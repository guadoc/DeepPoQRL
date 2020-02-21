/*
 * toolbox.cpp
 *
 *  Created on: Dec 23, 2019
 *      Author: Michael Blot
 */
#ifndef TOOLBOX
#define TOOLBOX


#include "StdAfx.h"
using namespace std;

static void progress_bar(float percentage){
	unsigned int N_char_to_print = 100;
	unsigned int n_done = (unsigned int) max((float)1., N_char_to_print * percentage);
	string bar = "[";
	for (unsigned int i = 0; i<n_done-1; i++){
		bar+="=";
	}
	bar += ">";
	for (unsigned int i = 0; i<N_char_to_print - n_done; i++){
		bar+=" ";
	}
	bar += "]" + to_string((int)(percentage*100)) + "%";
	cout<< "\r" + bar<<flush;
}


static void progress_bar(unsigned int iter, unsigned int total_iter){
	progress_bar((float)(iter+1) / float(total_iter));
	if(iter == total_iter){
		cout<<endl;
	}
}


template<typename ListType>
static void list_to_scv(string filename, ListType list){
	ofstream out_file(filename);
	if (out_file.fail()){
		//create file
		cout << "File does not exist, creating "<<filename << endl;
		string command = "touch " + filename;
		system(command.c_str());
		out_file = ofstream(filename);
	}
	for(auto const & value :list){
		out_file<<value<<",";
	}
	out_file<<"\n";
	out_file.close();
}

static list<float> average_list(list<float> const &list_to_average, unsigned int n_average){
	list<float> averaged_list;
	unsigned int i = 0;
	float avg = 0;
	for(float const & value: list_to_average){
		avg += value / n_average;
		if(i%n_average == 0){
			averaged_list.push_back(avg);
			avg = 0;
		}
		i++;
	}
	return averaged_list;
}

#endif
