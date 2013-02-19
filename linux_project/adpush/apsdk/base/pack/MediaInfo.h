/****************************************************************************************************************************
�汾������	����������Ϣ�����������ι�˾
�ļ�����	MediaInfo.h
�����ˣ�	����ΰ
�������ڣ�	2007-02-06
�汾�ţ�	1.00.000
˵����		����Ƶ���ݰ�����
*****************************************************************************************************************************/
#ifndef _MEDIA_INFO_H_
#define _MEDIA_INFO_H_

#include "StandardSerialize.h"

/*********************************************************************************************/
//�����Ƶ������Ϣ
/*********************************************************************************************/
struct	STRU_AUDIO_CONFIG
{
	uint8_t	mbyCodecType;				//ʹ�õı��������
	int	mlSamplesPerSec;   				//����Ƶ��
	//(8000/11025/12000/16000/22050/32000/44100(Hz))
	uint16_t    mwKBitsPerSec;        		//�������(kbps)
	uint8_t    mbyChannels;				//����ͨ����(1Ϊ������,2Ϊ������)
	uint8_t    mbyBitsPerSample;   		//������С(λ)

	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//�����Ƶ������Ϣ
/*********************************************************************************************/
struct STRU_VIDEO_CONFIG
{
	uint8_t	mbyCodecType;				//��Ƶ��������
	uint8_t	mbySizeType;				//��Ƶ��С����
	unsigned int	mdwBandWidth;				//��Ƶռ�ô�����λkbits��
	uint8_t	mbyFramePerSecond;			//��Ƶ֡�ʣ�0Ϊ��̬������1��15Ϊʵ������֡�ʣ�	

	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//�����˵���Ƶ��Ϣ
/*********************************************************************************************/
class STRU_VIDEO_INFO
{
public:
	uint8_t	mbyCodecType;				//��Ƶ��������
	uint8_t	mbyFramePerSecond;			//��Ƶ֡�ʣ�0Ϊ��̬������1��15Ϊʵ������֡�ʣ�

	uint16_t	mwFrameWidth;				//ͼ����
	uint16_t	mwFrameHeight;				//ͼ��߶�
	uint16_t	mwBitCount;					//λͼ��ɫ���
	unsigned int	mulChannelID;				//��Ƶͨ��ID

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_VIDEO_INFO(){}
	~STRU_VIDEO_INFO(){}
	STRU_VIDEO_INFO(STRU_VIDEO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mbyFramePerSecond = info.mbyFramePerSecond;
			mwFrameWidth = info.mwFrameWidth;
			mwFrameHeight = info.mwFrameHeight;
			mwBitCount = info.mwBitCount;
			mulChannelID = info.mulChannelID;
		}
	}

	STRU_VIDEO_INFO& operator=(const STRU_VIDEO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mbyFramePerSecond = info.mbyFramePerSecond;
			mwFrameWidth = info.mwFrameWidth;
			mwFrameHeight = info.mwFrameHeight;
			mwBitCount = info.mwBitCount;
			mulChannelID = info.mulChannelID;
		}
		return *this;
	}
};

/*********************************************************************************************/
//�����˵���Ƶ��Ϣ
/*********************************************************************************************/
class STRU_AUDIO_INFO
{
public:
	uint8_t	mbyCodecType;				//ʹ�õı��������
	int	mlSamplesPerSec;   				//����Ƶ��
	//(8000/11025/12000/16000/22050/32000/44100(Hz))
	uint16_t    mwKBitsPerSec;        		//�������(kbps)
	uint8_t    mbyChannels;				//����ͨ����(1Ϊ������,2Ϊ������)
	uint8_t    mbyBitsPerSample;   		//������С(λ)
	unsigned int	mulChannelID;				//��Ƶͨ��ID

	STRU_AUDIO_INFO(){}
	~STRU_AUDIO_INFO(){}
	STRU_AUDIO_INFO(STRU_AUDIO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mlSamplesPerSec = info.mlSamplesPerSec;
			mwKBitsPerSec = info.mwKBitsPerSec;
			mbyChannels = info.mbyChannels;
			mbyBitsPerSample = info.mbyBitsPerSample;
			mulChannelID = info.mulChannelID;
		}
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_AUDIO_INFO& operator=(const STRU_AUDIO_INFO& info)
	{
		if (&info != this)
		{
			mbyCodecType = info.mbyCodecType;
			mlSamplesPerSec = info.mlSamplesPerSec;
			mwKBitsPerSec = info.mwKBitsPerSec;
			mbyChannels = info.mbyChannels;
			mbyBitsPerSample = info.mbyBitsPerSample;
			mulChannelID = info.mulChannelID;
		}
		return *this;
	}
};
#endif //_MEDIA_INFO_H_
