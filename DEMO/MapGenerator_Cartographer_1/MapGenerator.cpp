#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <jsoncpp/json/json.h>

using namespace std;

struct submap
{
	string filename;
	string start_filename;
	double x;
	double y;
	double heading;
	int trim;
};

struct point
{
	double x;
	double y;
	double heading;
};

struct segment
{
	string filename;
	string start_index;
	double start_x;
	double start_y;
	double start_heading;
	string end_index;
	double end_x;
	double end_y;
	double end_heading;
};

point Local2Global(point p, point start_p);
double Rad2Deg(double Rad);
double Deg2Rad(double Deg);
double ReverseAngle(double angle);
double AngleConstrain(double angle);
Json::Value createjson();
Json::Value editmapdata(Json::Value input);

const string submaps_filename = "input/submaps.txt";
const string segments_filename = "input/segments.txt";

const string topo_filename = "lines/topo.txt";

const string map_filename = "output/map.txt";
const string json_filename = "output/map_full.json";

boost::format input_file_path("input/%s");
boost::format lines_file_path("lines/%s");

int main()
{
	remove(map_filename.c_str());
	remove(topo_filename.c_str());

	string s;
	point p;
	segment seg;
	int point_cnt = 0;
	string s2e_filename, e2s_filename;
	string start_point, end_point;
	int submap_index;

	queue<segment> segments;

	vector<submap> submaps;
	vector<point> segment_points;

	ifstream submaps_file(submaps_filename.c_str());
	ifstream segments_file(segments_filename.c_str());

	Json::StyledWriter jwriter;
	Json::Value jtopo;
	Json::Value mapdata;

    if(!(submaps_file.is_open() && segments_file.is_open()))
		return 0;

	while(getline(submaps_file, s))
	{
		if(s.empty())
			continue;

		stringstream ss(s);
		submap smap;
		ss >> smap.filename >> smap.start_filename >> smap.x >> smap.y >> smap.heading >> smap.trim;
		submaps.push_back(smap);
	}
	submaps_file.close();
	remove(submaps_filename.c_str());

	while(getline(segments_file, s))
	{
		if(s.empty())
			continue;

		stringstream ss(s);
		ss >> seg.filename >> seg.start_index >> seg.start_x >> seg.start_y >> seg.start_heading >> seg.end_index >> seg.end_x >> seg.end_y >> seg.end_heading;
		seg.start_heading = Deg2Rad(seg.start_heading);
		seg.end_heading = Deg2Rad(seg.end_heading);
		segments.push(seg);
	}
	segments_file.close();

	for(int i = 0; i < submaps.size(); i++)
	{
		queue<point> submap_points;

		string submap_filename = (input_file_path % submaps[i].filename).str();
		ifstream submap_file(submap_filename.c_str());

		while(getline(submap_file, s))
		{
			if(s.empty())
				continue;

			stringstream ss(s);
			ss >> p.x >> p.y >> p.heading;
			p.heading = Deg2Rad(p.heading);
			submap_points.push(p);
		}
		submap_file.close();

		if(i != 0)
		{
			ifstream start_file((lines_file_path % submaps[i].start_filename).str().c_str());
			while(getline(start_file, s))
			{
				if(s.empty())
					continue;

				stringstream ss(s);
				ss >> s >> s >> p.x >> s >> p.y >> s >> s >> p.heading;
			}
			start_file.close();

			submaps[i].x = p.x;
			submaps[i].y = p.y;

			if(!submaps[i].trim)
				submaps[i].heading = p.heading;
		}

		while(1)
		{
			if(!segments.empty())
				seg = segments.front();
			else
				break;

			if(seg.filename != submaps[i].filename)
				break;

			if(!submap_points.empty())
			{
				p = submap_points.front();
				submap_points.pop();
			}

			if(p.x == seg.start_x && p.y == seg.start_y && p.heading == seg.start_heading)
			{
				segment_points.clear();
			}

			segment_points.push_back(p);

			if(p.x == seg.end_x && p.y == seg.end_y && p.heading == seg.end_heading)
			{
				segments.pop();

				point_cnt++;

				submap_index = atoi(submaps[i].filename.substr(0, submaps[i].filename.size() - 4).c_str());

				stringstream ss;
				ss << submap_index;
        		ss >> s2e_filename;
				e2s_filename = s2e_filename;

				p.x = submaps[i].x;
				p.y = submaps[i].y;
				p.heading = submaps[i].heading;

				start_point = seg.start_index;
				end_point = seg.end_index;

				s2e_filename += "(" + start_point + "-" + end_point + ").txt";
				e2s_filename += "(" + end_point + "-" + start_point + ").txt";

				ofstream topo_file(topo_filename.c_str(), ios::app);
				topo_file << start_point << " " << end_point << " " << s2e_filename << " " << e2s_filename << endl;
				topo_file.close();

				s2e_filename = (lines_file_path % s2e_filename).str();
				e2s_filename = (lines_file_path % e2s_filename).str();

				ofstream s2e_file(s2e_filename.c_str());
				ofstream e2s_file(e2s_filename.c_str());
				ofstream map_file(map_filename.c_str(), ios::app);

				for(int j = 0; j < segment_points.size(); j++)
				{
					segment_points[j] = Local2Global(segment_points[j], p);

					s2e_file << 0 << " " << 0 << " " << segment_points[j].x << " " << 0 << " " << segment_points[j].y << " " << "a b " << segment_points[j].heading << " " << submap_index << " " << 0 << endl;
					map_file << segment_points[j].x << " " << segment_points[j].y << endl;
				}
				for(int j = segment_points.size() - 1; j >= 0; j--)
				{
					e2s_file << 0 << " " << 0 << " " << segment_points[j].x << " " << 0 << " " << segment_points[j].y << " " << "a b " << ReverseAngle(segment_points[j].heading) << " " << submap_index << " " << 0 << endl;
				}

				s2e_file.close();
				e2s_file.close();
				map_file.close();
			}
		}

		ofstream submaps_file(submaps_filename.c_str(), ios::app);
		submaps_file << submaps[i].filename << " " << submaps[i].start_filename << " " << submaps[i].x << " " << submaps[i].y << " " << submaps[i].heading << " " << submaps[i].trim << endl;
	}

	jtopo = createjson();
	mapdata = editmapdata(jtopo);

	ofstream json_file(json_filename.c_str());
	json_file << jwriter.write(mapdata);
	json_file.close();

    return 0;
}

point Local2Global(point p, point start_p)
{
	point global;

	global.x = p.x * cos(-start_p.heading) - p.y * sin(-start_p.heading) + start_p.x;
	global.y = p.x * sin(-start_p.heading) + p.y * cos(-start_p.heading) + start_p.y;
	global.heading = p.heading + start_p.heading;
	global.heading = AngleConstrain(global.heading);

	return global;
}

double Rad2Deg(double Rad)
{
	return Rad * 180.0 / M_PI;
}

double Deg2Rad(double Deg)
{
	return Deg * M_PI / 180.0;
}

double ReverseAngle(double angle)
{
	if(angle > 0)
		angle -= M_PI;
	else
		angle += M_PI;

	return angle;
}

double AngleConstrain(double angle)
{
	if(angle > M_PI)
	{
		angle = angle - 2 * M_PI;
	}
	else if(angle < -M_PI)
	{
		angle = angle + 2 * M_PI;
	}

	return angle;
}

Json::Value createjson()
{
	Json::StyledWriter writer;
	Json::Value final;
	Json::Value newobject;

	ifstream infile;
	infile.open(topo_filename.c_str());
	string temp;
	list<string> data;
	stringstream ss;
	data.clear();

	while(!infile.eof())
	{
		temp.clear();
		getline(infile, temp);
		data.push_back(temp);
	}
	infile.close();

	final.clear();

	int s_size = data.size() - 1;
	for(int i = 0; i < s_size; i++)
	{
		string sfnode, stnode, fname, bname;
		int fnode, tnode;
		ss.clear();
		ss << data.front();
		getline(ss, sfnode, ' ');
		getline(ss, stnode, ' ');
		getline(ss, fname, ' ');
		getline(ss, bname);
		fnode = boost::lexical_cast<int>(sfnode);
		tnode = boost::lexical_cast<int>(stnode);

		newobject.clear();
		newobject["attributes"]["CONVERAGE_"] = i + 1;
		newobject["attributes"]["FNODE_"] = fnode;
		newobject["attributes"]["TNODE_"] = tnode;
		newobject["attributes"]["LENGTH"] = 0;
		newobject["attributes"]["FNAME_"] = fname;
		newobject["attributes"]["BNAME_"] = bname;
		newobject["geometry"]["paths"]["front"][0] = 0;
		newobject["geometry"]["paths"]["back"][0] = 0;
		final["features"].append(newobject);

		data.pop_front();
	}

	ofstream outfile;
	outfile.open(json_filename.c_str());
	outfile << writer.write(final);
	outfile.close();

	return final;
}

Json::Value editmapdata(Json::Value input)
{
	Json::Value value;
	Json::Value deleted;
	Json::Value newpoint;
	value = input;

	ifstream infile;

	for(int i = 0; i < value["features"].size(); i++)
	{
		string fname = value["features"][i]["attributes"]["FNAME_"].asString();
		string bname = value["features"][i]["attributes"]["BNAME_"].asString();

		value["features"][i]["geometry"].removeMember("paths");

		newpoint.clear();

		ifstream gpsin;
		gpsin.open(((lines_file_path % fname).str()).c_str());
		string temp;
		list<string> temps;

		while(!gpsin.eof())
		{
			temp.clear();
			getline(gpsin, temp);
			temps.push_back(temp);
		}
		gpsin.close();

		string sx, sy, slat, sheiget, slon, pointcloud1, pointcloud2, sheading, skeyframe, sturnpoint;
		double lat, height, lon, heading;
		stringstream ss;
		ss.clear();

		int size = temps.size() - 1;
		for(int j = 0; j < size; j++)
		{
			ss.clear();
			ss << temps.front();
			getline(ss, sx, ' ');
			getline(ss, sy, ' ');
			getline(ss, slat, ' ');
			getline(ss, sheiget, ' ');
            getline(ss, slon, ' ');
            getline(ss, pointcloud1, ' ');
            getline(ss, pointcloud2, ' ');
            getline(ss, sheading, ' ');
            getline(ss, skeyframe, ' ');
            getline(ss, sturnpoint);

            lat = boost::lexical_cast<double>(slat);
            height = boost::lexical_cast<double >(sheiget);
            lon = boost::lexical_cast<double>(slon);
            heading = boost::lexical_cast<double >(sheading);
            newpoint.clear();
            newpoint["coordinate"][0] = lat;
            newpoint["coordinate"][1] = height;
            newpoint["coordinate"][2] = lon;
            newpoint["pointcloud1"] = pointcloud1;
            newpoint["pointcloud2"] = pointcloud2;
            newpoint["heading"] = heading;
			newpoint["keyframe"] = boost::lexical_cast<int>(skeyframe);

           	value["features"][i]["geometry"]["paths"]["front"].append(newpoint);
           	newpoint.clear();
           	temps.pop_front();
		}

		newpoint.clear();

		temps.clear();
		gpsin.open(((lines_file_path % bname).str()).c_str());

		while(!gpsin.eof())
		{
			temp.clear();
			getline(gpsin, temp);
			temps.push_back(temp);
		}
		gpsin.close();
		size = temps.size() - 1;

		for(int j = 0; j < size; j++)
		{
			ss.clear();
			ss << temps.front();
			getline(ss, sx, ' ');
			getline(ss, sy, ' ');
			getline(ss, slat, ' ');
			getline(ss, sheiget, ' ');               	
            getline(ss, slon, ' ');
            getline(ss, pointcloud1, ' ');
            getline(ss, pointcloud2, ' ');
            getline(ss, sheading, ' ');
            getline(ss, skeyframe, ' ');
            getline(ss, sturnpoint);

            lat = boost::lexical_cast<double>(slat);
            height = boost::lexical_cast<double >(sheiget);
            lon = boost::lexical_cast<double>(slon);
            heading = boost::lexical_cast<double >(sheading);
            newpoint.clear();
            newpoint["coordinate"][0] = lat;
            newpoint["coordinate"][1] = height;
            newpoint["coordinate"][2] = lon;
            newpoint["pointcloud1"] = pointcloud1;
            newpoint["pointcloud2"] = pointcloud2;
            newpoint["heading"] = heading;
			newpoint["keyframe"] = boost::lexical_cast<int>(skeyframe);

           	value["features"][i]["geometry"]["paths"]["back"].append(newpoint);
           	newpoint.clear();
           	temps.pop_front();
		}

		int path_size = value["features"][i]["geometry"]["paths"]["front"].size();
		int path_back_size = value["features"][i]["geometry"]["paths"]["back"].size();

		double x1 = value["features"][i]["geometry"]["paths"]["front"][0]["coordinate"][0].asDouble();
		double y1 = value["features"][i]["geometry"]["paths"]["front"][0]["coordinate"][2].asDouble();
		double x2 = value["features"][i]["geometry"]["paths"]["front"][path_size-1]["coordinate"][0].asDouble();
		double y2 = value["features"][i]["geometry"]["paths"]["front"][path_size-1]["coordinate"][2].asDouble();

		double x3 = value["features"][i]["geometry"]["paths"]["back"][0]["coordinate"][0].asDouble();
		double y3 = value["features"][i]["geometry"]["paths"]["back"][0]["coordinate"][2].asDouble();
		double x4 = value["features"][i]["geometry"]["paths"]["back"][path_back_size-1]["coordinate"][0].asDouble();
		double y4 = value["features"][i]["geometry"]["paths"]["back"][path_back_size-1]["coordinate"][2].asDouble();

		double di = hypot(x2 - x1, y2 - y1);
		double di2 = hypot(x4 - x3, y4 - y3);
		value["features"][i]["attributes"]["LENGTH"] = di >= di2 ? di : di2;
	}

	int point_size = 0;
	for(int i = 0; i < value["features"].size(); i++)
	{
		int tmp = value["features"][i]["attributes"]["FNODE_"].asInt();
		if(tmp > point_size)
		{
			point_size = tmp;
		}

		tmp = value["features"][i]["attributes"]["TNODE_"].asInt();
		if(tmp > point_size)
		{
			point_size = tmp;
		}
	}

	vector<int> pointvector;
	pointvector.resize(point_size);

	for(int i = 0; i < point_size; i++)
	{
		pointvector[i] = 0;
	}

	for(int i = 0; i < value["features"].size(); i++)
	{
		int fnode = value["features"][i]["attributes"]["FNODE_"].asInt();
		if(pointvector[fnode - 1] == 0)
		{
			newpoint.clear();
			double x = value["features"][i]["geometry"]["paths"]["front"][0]["coordinate"][0].asDouble();
			double height = value["features"][i]["geometry"]["paths"]["front"][0]["coordinate"][1].asDouble();
			double y = value["features"][i]["geometry"]["paths"]["front"][0]["coordinate"][2].asDouble();
			newpoint["id"] = fnode;
			newpoint["coordinate"][0] = x;
			newpoint["coordinate"][1] = height;
			newpoint["coordinate"][2] = y;
			value["points"]["point"].append(newpoint);
			pointvector[fnode - 1] = 1;
		}
	}

	for(int i = 0; i < value["features"].size(); i++)
	{
		int tnode = value["features"][i]["attributes"]["TNODE_"].asInt();
		if(pointvector[tnode - 1] == 0)
		{
			newpoint.clear();
			double x = value["features"][i]["geometry"]["paths"]["back"][0]["coordinate"][0].asDouble();
			double height = value["features"][i]["geometry"]["paths"]["back"][0]["coordinate"][1].asDouble();
			double y = value["features"][i]["geometry"]["paths"]["back"][0]["coordinate"][2].asDouble();
			newpoint["id"] = tnode;
			newpoint["coordinate"][0] = x;
			newpoint["coordinate"][1] = height;
			newpoint["coordinate"][2] = y;
			value["points"]["point"].append(newpoint);
			pointvector[tnode - 1] = 1;
		}
	}

	for(int i = 0; i < pointvector.size(); i++)
	{
		if(pointvector[i] == 0)
		{
			cout << "Fail" << endl;
			break;
		}

		if(i == pointvector.size() - 1 && pointvector[i] == 1)
		{
			cout << "Succeed" << endl;
		}
	}

	value["points"]["number"] = value["points"]["point"].size();

	return value;
}
