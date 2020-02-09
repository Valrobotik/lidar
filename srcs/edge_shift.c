#include "lidar.h"

#define	SET 1
#define	GET 0

int	set_get_flag(int setflag, int get_set)
{
	static int	flag;

	if (!flag)
		flag = 1;
	if (get_set == SET)
		flag = setflag;
	return (flag);
}

int	detect_rising(int value, int elmt)
{
	int	flag;
	int	ret;

	flag = set_get_flag(0, GET);
	if (flag & (1 << elmt))//old = 1
		ret = 0;
	else if (value == 1)//old = 0 && new = 1
		ret = 1;
	else
		ret = 0;
	flag = flag & ~(1 << elmt);//reset elm
	flag = flag | (value << elmt);//elm take value
	set_get_flag(flag, SET);
	return (ret);
}

int	detect_falling(int value, int elmt)
{
	int	flag;
	int	ret;

	flag = set_get_flag(0, GET);
	if (!(flag & (1 << elmt)))//old = 0
		ret = 0;
	else if (value == 0)//old = 1 && new = 0
		ret = 1;
	else
		ret = 0;
	flag = flag & ~(1 << elmt);//reset elm
	flag = flag | (value << elmt);//elm take value
	set_get_flag(flag, SET);
	return (ret);
}
