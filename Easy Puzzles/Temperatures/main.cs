using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

class Solution
{
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine()); // the number of temperatures to analyse
        string[] inputs = Console.ReadLine().Split(' ');
        int minVal = 0;
        int minDist = 10001;
        for (int i = 0; i < n; i++)
        {
            int t = int.Parse(inputs[i]);// a temperature expressed as an integer ranging from -273 to 5526
            int dist = Math.Abs(t - 0);
            if(dist < minDist){
                minDist = dist;
                minVal = t;
            }
            if(dist == minDist && minVal < t){
                minVal = t;
            }
        }

        Console.WriteLine(minVal);
    }
}
