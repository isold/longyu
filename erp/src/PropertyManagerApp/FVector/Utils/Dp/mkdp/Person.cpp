//////////////////
// Generated by makedp(1.0.0.0)
////////////////

#include "Person.h"


///////////////////////////
/////////////////// Person///////////////////////////
Person::Person(void)
	 : stuv(222),
	   he("hellow this is!!!"),
	   hafasf("xxxxxxA")
{
}


bool Person::load(Dp::Reader &r)
{
	Dp::SizeType structLen;  r >> structLen;
	Dp::SizeType structEnd = r.cursor() + structLen;

	//----- id -----
	r >> id;
	//----- sex -----
	r >> sex;
	//----- nick -----
	r >> nick;
	//----- address -----
	r >> address;
	if (!r.ok()) return false;

	while (r.cursor() < structEnd)
	{
		uint8_t mflag; r >> mflag;
		uint8_t mid = Dp::memberId(mflag);
		uint8_t msize = Dp::memberSize(mflag);

		switch (mid)
		{
		//----- stuv -----
		case 21: r >> stuv; break;
		//----- memo -----
		case 1: r >> memo; break;
		//----- data -----
		case 2: r >> data; break;
		//----- he -----
		case 10: r >> he; break;
		//----- hafasf -----
		case 11: r >> hafasf; break;
		default:
			switch (msize)
			{
			case Dp::TypesEnum::size_8: r.skip(1); break;
			case Dp::TypesEnum::size_16:r.skip(2); break;
			case Dp::TypesEnum::size_32:r.skip(4); break;
			case Dp::TypesEnum::size_64:r.skip(8); break;
			case Dp::TypesEnum::size_array: { Dp::SizeType as; r >> as; r.skip(as); } break;
			default:break;
			}
			break;
		}

		if (!r.ok()) return false;
	}
	return true;
}

void Person::save(Dp::Writer &w)
{
	Dp::SizeType start = w.cursor();
	w.skip(sizeof(Dp::SizeType));

	//----- id -----
	w << id;
	//----- sex -----
	w << sex;
	//----- nick -----
	w << nick;
	//----- address -----
	w << address;
	//----- stuv -----
	if (stuv != 222)
		w << Dp::makeMemberFlag(21,Dp::TypesEnum::size_32) << stuv;
	//----- memo -----
	if (!memo.empty())
		w << Dp::makeMemberFlag(1,Dp::TypesEnum::size_array) << memo;
	//----- data -----
	if (!data.empty())
		w << Dp::makeMemberFlag(2,Dp::TypesEnum::size_array) << data;
	//----- he -----
	if (!he.empty())
		w << Dp::makeMemberFlag(10,Dp::TypesEnum::size_array) << he;
	//----- hafasf -----
	if (!hafasf.empty())
		w << Dp::makeMemberFlag(11,Dp::TypesEnum::size_array) << hafasf;

	Dp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);
	w.set(start,&len,sizeof(Dp::SizeType));
}


///////////////////////////
/////////////////// Person1///////////////////////////
Person1::Person1(void)
{
}


bool Person1::load(Dp::Reader &r)
{
	Dp::SizeType structLen;  r >> structLen;
	Dp::SizeType structEnd = r.cursor() + structLen;

	//----- id -----
	r >> id;
	//----- sex -----
	r >> sex;
	//----- nick -----
	r >> nick;
	//----- address -----
	r >> address;
	if (!r.ok()) return false;

	while (r.cursor() < structEnd)
	{
		uint8_t mflag; r >> mflag;
		uint8_t mid = Dp::memberId(mflag);
		uint8_t msize = Dp::memberSize(mflag);

		switch (mid)
		{
		//----- memo -----
		case 1: r >> memo; break;
		//----- sdata -----
		case 3: r >> sdata; break;
		//----- s11data -----
		case 4: r >> s11data; break;
		//----- hdata -----
		case 5: r >> hdata; break;
		//----- he -----
		case 10: r >> he; break;
		//----- hafasf -----
		case 11: r >> hafasf; break;
		default:
			switch (msize)
			{
			case Dp::TypesEnum::size_8: r.skip(1); break;
			case Dp::TypesEnum::size_16:r.skip(2); break;
			case Dp::TypesEnum::size_32:r.skip(4); break;
			case Dp::TypesEnum::size_64:r.skip(8); break;
			case Dp::TypesEnum::size_array: { Dp::SizeType as; r >> as; r.skip(as); } break;
			default:break;
			}
			break;
		}

		if (!r.ok()) return false;
	}
	return true;
}

void Person1::save(Dp::Writer &w)
{
	Dp::SizeType start = w.cursor();
	w.skip(sizeof(Dp::SizeType));

	//----- id -----
	w << id;
	//----- sex -----
	w << sex;
	//----- nick -----
	w << nick;
	//----- address -----
	w << address;
	//----- memo -----
	if (!memo.empty())
		w << Dp::makeMemberFlag(1,Dp::TypesEnum::size_array) << memo;
	//----- sdata -----
	if (!sdata.empty())
		w << Dp::makeMemberFlag(3,Dp::TypesEnum::size_array) << sdata;
	//----- s11data -----
	w << Dp::makeMemberFlag(4,Dp::TypesEnum::size_64) << s11data;
	//----- hdata -----
	w << Dp::makeMemberFlag(5,Dp::TypesEnum::size_64) << hdata;
	//----- he -----
	if (!he.empty())
		w << Dp::makeMemberFlag(10,Dp::TypesEnum::size_array) << he;
	//----- hafasf -----
	if (!hafasf.empty())
		w << Dp::makeMemberFlag(11,Dp::TypesEnum::size_array) << hafasf;

	Dp::SizeType len = w.cursor() - start - sizeof(Dp::SizeType);
	w.set(start,&len,sizeof(Dp::SizeType));
}


///////////////////////////
/////////////////// tagPerson///////////////////////////
tagPerson::tagPerson(void)
	 : ver(0),
	   len(0),
	   cmd(8)
{
}


bool tagPerson::load(Dp::Reader &r)
{
	//----- ver -----
	r >> ver;
	//----- len -----
	r >> len;
	//----- cmd -----
	r >> cmd;
	//----- p1 -----
	 p1.load(r);
	//----- ps -----
	load_some(r,ps);
	//----- ps1 -----
	raw_load_some(r,ps1);
	return r.ok();
}

void tagPerson::save(Dp::Writer &w)
{
	//----- ver -----
	w << ver;
	//----- len -----
	w << len;
	//----- cmd -----
	w << cmd;
	//----- p1 -----
	 p1.save(w);
	//----- ps -----
	save_some(w,ps);
	//----- ps1 -----
	raw_save_some(w,ps1);
}


