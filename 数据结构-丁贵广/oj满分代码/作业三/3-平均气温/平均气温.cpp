#include <stdio.h>
#include "temperature.h"
#define maxn 50000
using namespace std;
struct range_node;
typedef struct _station_type
{
	int x, y;
	int temp;
	_station_type&operator=(const _station_type&data)
	{
		temp = data.temp;
		x = data.x;
		y = data.y;
		return *this;
	}
	range_node*c,*road=NULL;
} station_type;
station_type stations[maxn];
struct fctree {
	station_type data;
	bool operator>(const fctree&a)
	{
		if (data.y > a.data.y)return true;
		else if (data.y == a.data.y) {
			if (data.x > a.data.x)return true;
			else return false;
		}
		else return false;
	}
	bool operator<(const fctree&a)
	{
		if (data.y < a.data.y)return true;
		else if (data.y == a.data.y) {
			if (data.x < a.data.x)return true;
			else return false;
		}
		else return false;
	}
};
struct range_node {
	range_node*rc, *lc, *parent;
	fctree*fc;
	int fc_size = 0;
	station_type data;
	int height = 0;
	range_node() { rc = lc = NULL; fc = NULL; parent = NULL; }
	range_node(const station_type&e, range_node*p, fctree*fc1 = NULL, range_node*lc1 = NULL, range_node*rc1 = NULL) :data(e), parent(p), fc(fc1), lc(lc1), rc(rc1) {}
};
struct rangetree {
	rangetree() { range_node(); }
	range_node*_hot;
	range_node*_root;
	range_node*&search(const int&e);
	void insertAsRoot(const station_type&e);
	range_node*insert(const station_type&data);
	range_node*&fromparento(range_node*g);
	range_node*connect34(range_node*a, range_node*b, range_node*c, range_node*t0, range_node*t1, range_node*t2, range_node*t3);
	range_node*rotateAt(range_node*g);
	void search_leaf(range_node*&v, int&i, range_node*hot);
	int size = 0;
};

bool operator==(const _station_type&data1, const _station_type&data2)
{
	return ((data1.x == data2.x) && (data1.y == data2.y));
}
int stature(range_node*a) { return a ? a->height : -1; }
void rangetree::insertAsRoot(const station_type&e)
{
	_root = new range_node(e, NULL); size++;
}
range_node*&searchin(range_node*&v, const int&e, range_node*&hot)
{
	if (!v)return v;
	hot = v;
	return searchin((e <= v->data.x) ? v->lc : v->rc, e, hot);
}
range_node*&rangetree::search(const int&e)
{
	return searchin(_root, e, _hot = NULL);
}
bool Balance(range_node a) { return (stature(a.lc) - stature(a.rc)) > -2 && stature(a.lc) - stature(a.rc) < 2; }
bool islchild(range_node*g) { return g->parent && (g->parent->lc == g); }
bool isrchild(range_node*g) { return g->parent && (g->parent->rc == g); }
void updateheight(range_node*g)
{
	if (stature(g->lc)>stature(g->rc)) { g->height = stature(g->lc) + 1; }
	else { g->height = stature(g->rc) + 1; }
}
range_node*tallerchild(range_node*g)
{
	return (stature(g->lc) > stature(g->rc)) ? g->lc : (((stature(g->lc) <stature(g->rc)) ? g->rc : (islchild(g) ? g->lc : g->rc)));
}
range_node*&rangetree::fromparento(range_node*g)
{
	if (g->parent) { return islchild(g) ? g->parent->lc : g->parent->rc; }
	else { return _root; }
}
range_node*rangetree::insert(const station_type&data)
{
	range_node*&x = search(data.x);
	range_node*xx = x = new range_node(data, _hot);
	for (range_node*g = _hot; g; g = g->parent)
	{
		if (!Balance(*g)) {
			auto&temp = fromparento(g);
			temp = rotateAt(tallerchild(tallerchild(g)));
			break;
		}
		else updateheight(g);
	}
	size++;
	return xx;
}
range_node*rangetree::connect34(range_node*a, range_node*b, range_node*c, range_node*t0, range_node*t1, range_node*t2, range_node*t3)
{
	a->lc = t0; if (t0) { t0->parent = a; }
	a->rc = t1; if (t1) { t1->parent = a; }
	updateheight(a);
	c->lc = t2; if (t2) { t2->parent = c; }
	c->rc = t3; if (t3) { t3->parent = c; }
	updateheight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateheight(b);
	return b;
}
range_node*rangetree::rotateAt(range_node*v)
{
	range_node*p = v->parent;
	range_node*g = p->parent;
	if (islchild(p)) {
		if (islchild(v)) {
			p->parent = g->parent;
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else {
		if (islchild(v)) {
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
		else {
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
	}
} 
bool isleaf(range_node*root) {
	return root && (!root->lc && !root->rc);
}
int n;
long long int  record = 0;
int count;
station_type stack_x1[100], stack_x2[100];
int road_x1, road_x2;
void merge_y(fctree*&a1, fctree data_lc[], fctree data_rc[], int n_lc, int n_rc)
{
	a1 = new fctree[n_lc + n_rc];
	int i = 0, j = 0, k = 0;
	while (i < n_lc&&j < n_rc)
	{
		if (data_lc[i] < data_rc[j])a1[k++].data = data_lc[i++].data;
		else a1[k++].data = data_rc[j++].data;
	}
	if (i == n_lc)
		while (k<n_lc + n_rc)
		{
			a1[k++].data = data_rc[j++].data;
		}
	else
		while (k<n_lc + n_rc)
		{
			a1[k++].data = data_lc[i++].data;
		}
}
void rangetree::search_leaf(range_node*&v, int&i, range_node*hot)
{
	if (!v) {
		if (i < n)
		{
			stations[i].c = v = new range_node(stations[i], hot);
			v->fc = new fctree[1]; 
			v->fc->data = stations[i++];
			(v->fc_size)++;
		}
	}
	else {
		hot = v;
		search_leaf(v->lc, i, hot);
		search_leaf(v->rc, i, hot);
		if (v->lc && v->rc)
		{
			merge_y(v->fc, v->lc->fc, v->rc->fc, v->lc->fc_size, v->rc->fc_size);
			v->fc_size = v->lc->fc_size + v->rc->fc_size;
		}
		else
		{
			v->fc = new fctree[v->lc->fc_size];
			for (auto i = 0; i < v->lc->fc_size; i++)v->fc[i].data = v->lc->fc[i].data;
			v->fc_size = v->lc->fc_size;
		}
	}
}
//用于对x进行2分查找
void merge_x(station_type data[], int lo, int mi, int hi)
{
	station_type*a1 = new station_type[mi - lo];
	int k = lo, i = 0, t = mi - lo;
	for (auto i = 0; i < mi - lo; i++)a1[i] = data[k++];
	while ((mi< hi) && (i<t))
	{
		if (a1[i].x < data[mi].x)data[lo++] = a1[i++];
		else if (a1[i].x == data[mi].x&&a1[i].y < data[mi].y)data[lo++] = a1[i++];
		else data[lo++] = data[mi++];
	}
	if (i == t);
	else while (lo < hi)data[lo++] = a1[i++];
	delete[]a1;
}
void mergesort_x(station_type data[], int lo, int hi)
{
	int mi;
	if (hi - lo > 1) {
		mi = (hi + lo) >> 1;
		mergesort_x(data, lo, mi);
		mergesort_x(data, mi, hi);
		merge_x(data, lo, mi, hi);
	}
	else return;
}
//寻找x1和x2
void search_x1(range_node*root, int x1, int x2, station_type stack[], int&road, int lo, int hi)
{
	int lenght = hi;
	while (hi > lo)
	{
		int mi = (hi + lo) >> 1;
		(stations[mi].x<x1) ? lo = mi + 1 : hi = mi;
	}
	if (lo<lenght&& stations[lo].x <= x2) {
		auto root = stations[lo].c;
		while (root)
		{
			stack[road] = root->data;
			stack[road].c = root;
			if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
			road++;
			root = root->parent;
			
		}
	}
	else;
}
void search_x2(range_node*root, int x1, int x2, station_type stack[], int&road, int lo, int hi)
{
	int lenght = hi;
	while (hi > lo)
	{
		int mi = (hi + lo) >> 1;
		(stations[mi].x > x2) ? hi = mi : lo = mi + 1;
	}
	--lo;
	if (lo > -1 && stations[lo].x >= x1) {
		auto root = stations[lo].c;
		while (root)
		{
			stack[road] = root->data;
			stack[road].c = root;
			if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
			road++;
			root = root->parent;
		}
	}
	else;
}
range_node*common_root()
{
	while (0 < road_x1 && 0 < road_x2&&stack_x1[--road_x1] == stack_x2[--road_x2]);
	return (stack_x1[road_x1] == stack_x2[road_x2]) ? stack_x1[road_x1].c : stack_x1[++road_x1].c;
}
void search_y(range_node*root, int lo, int hi, int y1, int y2)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		(y1 <= root->fc[mi].data.y) ? hi = mi : lo = mi + 1;
	}
	while (lo < root->fc_size&&root->fc[lo].data.y <= y2  )
	{
		record += root->fc[lo].data.temp;
		count++;
		lo++;
	}
}
void travelReport(int x1,int x2,int y1, int y2)
{
	while (road_x1 >= 0)
	{
		auto rc = stack_x1[road_x1].c->rc;
		auto lc = stack_x1[road_x1].c->lc;
		auto road = stack_x1[road_x1].road;
		if (rc&&rc!=road)search_y(rc, 0, rc->fc_size, y1, y2);
		road_x1--;
	}
	auto now = stack_x1[road_x1 + 1].c;
	if (now->data.x >= x1 &&now->data.x <= x2 && now->data.y >= y1 && now->data.y <= y2)
	{
		count++;
		record += now->data.temp;
	}
	while (road_x2 >= 0)
	{
		auto rc = stack_x2[road_x2].c->rc;
		auto lc = stack_x2[road_x2].c->lc;
		auto road = stack_x2[road_x2].road;
		if (lc&&lc != road)search_y(lc, 0, lc->fc_size, y1, y2);
		road_x2--;
	}
	auto now2 = stack_x2[road_x2 + 1].c;
	if (now2->data.x >= x1 && now2->data.x <= x2 && now2->data.y >= y1 && now2->data.y <= y2)
	{
		count++;
		record += now2->data.temp;
	}
}
int main()
{
	n = GetNumOfStation();
	if (n == 0) {
		int x1, x2, y1, y2;
		while (GetQuery(&x1, &y1, &x2, &y2)) {
			Response(0); printf("0\n");
		}
		return 0;
	}
	rangetree a;
	for (auto i = 0; i < n; i++)GetStationInfo(i, &(stations[i].x), &(stations[i].y), &(stations[i].temp));
	a.insertAsRoot(stations[0]);
	for (auto i = 1; i < n; i++)a.insert(stations[i]);
	mergesort_x(stations, 0, n);
	int i = 0;
	a._hot = NULL;
	a.search_leaf(a._root, i, a._hot);
	int x1, x2, y1, y2, num = 1;
	while (GetQuery(&x1, &y1, &x2, &y2))
	{
		search_x1(a._root, x1, x2, stack_x1, road_x1, 0, n);
		search_x2(a._root, x1, x2, stack_x2, road_x2, 0, n);
		int t1 = road_x1, t2 = road_x2;
		if (road_x1&&road_x2)
		{
			range_node*v = common_root();
				road_x1--;
				travelReport(x1,x2,y1, y2);
			if (count != 0) {
				Response(record / count);
			}
			else {
				Response(0);
			}
		}
		else {
			Response(0);
		}
		for (auto i = 0; i < t1; i++) { stack_x1[i].c = NULL; stack_x1[i].road = NULL; stack_x1[i].x = 0; stack_x1[i].y = 0; stack_x1[i].temp = 0; }
		for (auto i = 0; i <t2; i++) { stack_x2[i].c = NULL; stack_x1[i].road = NULL; stack_x2[i].x = 0; stack_x2[i].y = 0; stack_x2[i].temp = 0; }
		t1 = t2 = road_x1 = road_x2 = record = count = 0;
	}
}
