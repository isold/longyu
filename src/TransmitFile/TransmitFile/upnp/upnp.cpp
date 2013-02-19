#include "stdafx.h"
#include "upnp.h"

CUpnpNat::CUpnpNat()
:m_sPort(13800)
{
	AddPortMapping();
}

CUpnpNat::~CUpnpNat()
{
	DelPortMapping();
}
int CUpnpNat::AddPortMapping()
{
	UPNPNAT nat;
	strstream strError;
	nat.init(5,5);
	if(!nat.discovery())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.get_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.parser_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;	
	}

	if(nat.add_port_mapping(m_sPort,"UDP"))
	{
		strError<<"�ɹ���Ӷ˿�ӳ�� UDP port = "<<m_sPort<<endl<<ends;
		ATLTRACE(strError.str());
		return 1;
	}
	else
	{
		strError<<"��Ӷ˿�ӳ��ʧ�� UDP: "<<m_sPort<<" ����"<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}
}

int CUpnpNat::DelPortMapping()
{
	UPNPNAT nat;
	strstream strError;
	nat.init(5,5);
	if(!nat.discovery())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.get_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}

	if(!nat.parser_description())
	{
		strError<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;	
	}

	if(nat.del_port_mapping(m_sPort,"UDP"))
	{
		strError<<"�ɹ�ɾ���˿�ӳ�� UDP"<<endl<<ends;
		ATLTRACE(strError.str());
		return 1;
	}
	else
	{
		strError<<"ɾ���˿�ӳ��ʧ�� UDP: "<<m_sPort<<" ����"<<nat.get_last_error()<<endl<<ends;
		ATLTRACE(strError.str());
		return -1;
	}
}