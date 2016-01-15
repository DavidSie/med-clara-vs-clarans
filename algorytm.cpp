/*
 * algorytm.cpp
 *
 *  Created on: 12 gru 2015
 *      Author: davidsiecinski
 */

#include "algorytm.h"


 void Algorytm::wypiszPunkt(punkt punkt_){
	 std::cout<<"[INFO] ( ";
	 for (int i=0; i<punkt_.size();i++)
		 std::cout<<punkt_.at(i)<<", ";
	 std::cout<<") "<<std::endl;
 }
