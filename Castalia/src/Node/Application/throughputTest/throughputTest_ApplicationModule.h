//***************************************************************************************
//*  Copyright: National ICT Australia,  2007, 2008, 2009				*
//*  Developed at the Networks and Pervasive Computing program				*
//*  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis				*
//*  This file is distributed under the terms in the attached LICENSE file.		*
//*  If you do not find this file, copies can be found by writing to:			*
//*											*
//*      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia			*
//*      Attention:  License Inquiry.							*
//*											*
//***************************************************************************************

 
 

#ifndef _THROUGHPUTTEST_APPLICATIONMODULE_H_
#define _THROUGHPUTTEST_APPLICATIONMODULE_H_

#include "VirtualCastaliaModule.h"

#include <string>
#include <map>
#include "SensorDevMgr_GenericMessage_m.h"
#include "throughputTest_DataPacket_m.h"
#include "App_GenericDataPacket_m.h"
#include "App_ControlMessage_m.h"
#include "NetworkControlMessage_m.h"
#include "ResourceGenericManager.h"

using namespace std;

struct packet_info
{
    map <int, bool> packets_received;
};

class throughputTest_ApplicationModule : public VirtualCastaliaModule
{
	private:
	// parameters and variables
	
	/*--- The .ned file's parameters ---*/
		string applicationID;
		bool printDebugInfo;

		int latencyHistogramMin;
		int latencyHistogramMax;
		int latencyHistogramBuckets;

		int priority;
		int maxAppPacketSize;
		int packetHeaderOverhead;
		int constantDataPayload;
		int nextRecipient;
		double packet_rate;
	
	/*--- Latency calculation parameters ---*/
		cLongHistogram latencyHistogram;
		int latencyOverflow;
		
	/*--- Custom class parameters ---*/
		int self;	// the node's ID
		ResourceGenericManager *resMgrModule;	//a pointer to the object of the Radio Module (used for direct method calls)
		int disabled;
		double cpuClockDrift;
		
		float packet_spacing;
		map <int, packet_info> packet_info_table; // this table records the number of packets received by node 0 from each other node
		int total_packets_received;
		int packets_lost_at_mac;
		int packets_lost_at_network;
		int dataSN;
		
		char selfAddr[16];
		char dstAddr[16];
    		
	protected:
		virtual void initialize();
		virtual void handleMessage(cMessage *msg);
		virtual void finishSpecific();
		
		void send2NetworkDataPacket(const char *destID, int data, int pckSeqNumber);
		void requestSampleFromSensorManager();
		
		
		/************ Header file for Declaration of Functions of TunableMAC set functions  ******************************/
		// If you are not going to use the TunableMAC module, then you can comment the following line and build Castalia
		// the following includes are located at ../commonIncludeFiles
		#include "radioControl.h"
		#include "tunableMacControl.h"
		/************ Connectivity Map Definitions  ************************************************/
		

		/**
		   ADD HERE YOUR CUSTOM protected MEMBER VARIABLES AND FUNCTIONS
		 **/
		void update_packets_received(int srcID, int SN);

	public:
		/**
		   ADD HERE YOUR CUSTOM public MEMBER VARIABLES AND FUNCTIONS
		 **/
};

#endif // _THROUGHPUTTEST_APPLICATIONMODULE_H_
