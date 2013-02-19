
/***************************************************************************************************************************
�汾������	����������Ϣ�����������ι�˾
�ļ�����	MediaInfo.cpp
�����ˣ�	����ΰ
�������ڣ�	2007-02-07
�汾�ţ�	1.00.000
˵����		����Ƶ���ݰ�ʵ��
*****************************************************************************************************************************/
#include "StandardSerialize.h"
#include "MediaInfo.h"

/*********************************************************************************************/
//�����Ƶ������Ϣ
/*********************************************************************************************/
int STRU_AUDIO_CONFIG::Serialize(CStandardSerialize & aoStandardSerialize)
{

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mlSamplesPerSec);
		aoStandardSerialize.Serialize(mwKBitsPerSec);
		aoStandardSerialize.Serialize(mbyChannels);
		aoStandardSerialize.Serialize(mbyBitsPerSample);
		return 1;
}

/*********************************************************************************************/
//�����Ƶ������Ϣ
/*********************************************************************************************/
int STRU_VIDEO_CONFIG::Serialize(CStandardSerialize & aoStandardSerialize)
{	

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mbySizeType);
		aoStandardSerialize.Serialize(mdwBandWidth);
		aoStandardSerialize.Serialize(mbyFramePerSecond);
		return 1;
}

//*/
/*********************************************************************************************/
//�����˵���Ƶ��Ϣ
/*********************************************************************************************/
int STRU_VIDEO_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mbyFramePerSecond);

		aoStandardSerialize.Serialize(mwFrameWidth);
		aoStandardSerialize.Serialize(mwFrameHeight);
		aoStandardSerialize.Serialize(mwBitCount);
		aoStandardSerialize.Serialize(mulChannelID);
		return 1;

}

/*********************************************************************************************/
//�����˵���Ƶ��Ϣ
/*********************************************************************************************/
int STRU_AUDIO_INFO::Serialize(CStandardSerialize & aoStandardSerialize)
{

		aoStandardSerialize.Serialize(mbyCodecType);
		aoStandardSerialize.Serialize(mlSamplesPerSec);
		aoStandardSerialize.Serialize(mwKBitsPerSec);
		aoStandardSerialize.Serialize(mbyChannels);
		aoStandardSerialize.Serialize(mbyBitsPerSample);
		aoStandardSerialize.Serialize(mulChannelID);
		return 1;
}
