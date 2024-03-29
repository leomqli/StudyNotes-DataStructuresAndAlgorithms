//
//  DP Note.swift
//  DataStructuresAndAlgorithms
//
//  Created by Leo on 2023/10/10.
//

/*
 
 动态规划
 
 动态规划(Dynamic Programming，简称 DP)是一种在数学、管理科学、计算机科学、经济学和生物信息学中使⽤的，通过把原问题分解为相对简单的子问题的方式求解复杂问题的方法。
 
 动态规划常常适用于有重叠子问题和最优子结构性质的问题，动态规划方法所耗时间往往远少于朴素解法。
 
 动态规划背后的基本思想非常简单。大致上，若要解⼀个给定问题，我们需要解其不同部分(即子问题)，再根据子问题的解以得出原问题的解。
 动态规划往往用于优化递归问题，例如斐波那契数列，如果运⽤递归的方式来求解会重复计算很多相同的子问题，利⽤动态规划的思想可以减少计算量。
 
 通常许多子问题非常相似，为此动态规划法试图仅仅解决每个⼦问题一次，具有天然剪枝的功能，从⽽减少计算量：
 一旦某个给定⼦问题的解已经算出，则将其记忆化存储，以便下次需要同⼀个⼦问题解之时直接查表。
 这种做法在重复子问题的数目关于输⼊的规模呈指数增长时特别有⽤。
 
 三个核心要素：
 1. 最优子结构;
 2. 边界；
 3. 状态转移方程式。
 
 题目类型：
	* 基础类：斐波那契数列、爬楼梯
	* 背包问题
	* 打家劫舍
	* 股票问题
	* 子序列问题
 
 解题步骤：
	1、DP数组及下标的含义；
	2、递推公式；
	3、DP数组如何初始化;
	4、遍历顺序；
	5、打印DP数组。
 
 */
