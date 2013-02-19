/***************************************************************************
 *   Copyright (C) 2006 by taofei   *
 *   gudu2005@126.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef UPNPNAT_H
#define UPNPNAT_H
#include <string>
#include <vector>

#define DefaultTimeOut  10
#define DefaultInterval 200

#include <winsock2.h>
#pragma comment(lib, "Ws2_32")


class UPNPNAT
{
public:
 
    bool init(int time_out=DefaultTimeOut,int interval=DefaultInterval); 
                            		//��ʼ���������ó�ʱ����������� 
    bool discovery();       		//�����豸������describe_url�����豸����URL 
    bool get_description();			//ȡ���豸����XML�ļ�
    bool parser_description();		//�����豸����XML�ļ� ��ÿ���URL
    bool add_port_mapping(unsigned short int _port,const char * _protocal);	//���һ���˿�ӳ��
    bool del_port_mapping(unsigned  short int _port,const char * _protocal);//ɾ��һ���˿�ӳ��
   	bool get_port_mapping();                                                //������еĶ˿�ӳ����Ϣ
    const char * get_last_error(){ return last_error.c_str();}             //������һ������
private:
	bool get_localIP();
	bool tcp_connect(const char * _addr,unsigned short int _port);
	bool parse_mapping_info();												//����һ���˿�ӳ����Ϣ��
    int udp_socket_fd;
	int tcp_socket_fd;
	typedef enum 
	{
		NAT_INIT=0,
		NAT_FOUND,
		NAT_TCP_CONNECTED,
		NAT_GETDESCRIPTION,
		NAT_GETCONTROL,
		NAT_ADD,
		NAT_DEL,
		NAT_GET,
		NAT_ERROR
	} NAT_STAT;
	NAT_STAT status;
    int time_out;
    int interval;
	std::string local_ip;
	std::string service_type;
    std::string describe_url;
	std::string control_url;
	std::string base_url;
	std::string service_describe_url;
    std::string description_info;
	std::string mapping_info;
	std::vector<std::string> mapping_infos;
	std::string last_error;
	
};


#endif

