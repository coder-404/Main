// C++ includes used for precompiling -*- C++ -*-

// Copyright (C) 2003-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file stdc++.h
 *  This is an implementation file for a precompiled header.
 */

// 17.4.1.2 Headers

// C
#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
using namespace std;
const int maxn=100005;
#define ll long long
ll n,m,fa[maxn],li[maxn],w[maxn],rt[maxn],rx[maxn];
ll ans=0;
int dp[maxn],ls[maxn],rs[maxn],v[maxn],size[maxn],cnt=0;
ll sum[maxn];
//fa是父亲，li是领导力，w是薪水 
int Merge(int a,int b)
{
	if(!a||!b)return a+b;
	if(v[a]<v[b])
	{
		swap(a,b);
	}
	rs[a]=Merge(rs[a],b);
	if(dp[ls[a]]<dp[rs[a]])swap(ls[a],rs[a]);
	dp[a]=dp[rs[a]]+1;
	size[a]=size[ls[a]]+size[rs[a]]+1;
	sum[a]=sum[ls[a]]+sum[rs[a]]+v[a];
	return a;
}
int Pop(int rt)
{
	return Merge(ls[rt],rs[rt]);
}
vector<int>to[maxn];
int Newnode(int k)
{
	int rt=++cnt;
	sum[rt]=v[rt]=k;
	size[rt]=1;
	return rt;
}
void Set(int prt,int son)//建立一条从prt到son的边 
{
	to[prt].push_back(son);
}
void dfs(int rt)
{
	rx[rt]=Newnode(w[rt]);//为rt新建节点 
	//枚举儿子 
	for(int i=0;i<to[rt].size();i++)
	{
		int son=to[rt][i];
		dfs(son);//深搜 
		rx[rt]=Merge(rx[rt],rx[son]);//合并堆 
		while(sum[rx[rt]]>m)rx[rt]=Pop(rx[rt]);//把要求过高的忍者弹出 
	}
	ans=max(ans,li[rt]*1ll*size[rx[rt]]); 
} 
int main()
{
	//freopen("dispatching.in","r",stdin);
	//freopen("dispatching.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&fa[i],&w[i],&li[i]);
		Set(fa[i],i);
	}
	dfs(1);//从根节点开始深搜 
	printf("%lld\n",ans);
	return 0;
}
