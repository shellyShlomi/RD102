using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.IO;
using System.Linq;

namespace CompareTwoFiles
{
    class Program
    {
        static void Main(string[] args)
        {
            bool equal = true;
            if (args.Length < 1)
            {
                Console.WriteLine("No files recived.");
                return;
            }

            Console.WriteLine("Files are: " + args[0] + ", " + args[1]);
            StreamReader r1 = new StreamReader(args[0]);
            StreamReader r2 = new StreamReader(args[1]);


            IEnumerable<String> file1Lines = File.ReadLines(args[0]);
            IEnumerable<String> file2Lines = File.ReadLines(args[1]);


            long lengthe1 = file1Lines.Count();
            long lengthe2 = file2Lines.Count();

            Console.WriteLine("Comparisons of files shows :" + lengthe2);
            int line = 0;

            string s2;
            string s1;
            while (((s1 = r1.ReadLine()) != null) && (s2 = r2.ReadLine()) != null)
            {
                int val;
                if (0 > (val = s1.CompareTo(s2)))
                {
                    Console.WriteLine("file {0} is contines extra data then {1}", args[1], args[0]);
                }

                else if (val > 0)
                {
                    Console.WriteLine("file {0} is contines extra data then {1}", args[0], args[1]);
                }

                if (val != 0)
                {
                    Console.WriteLine("s1 line " + (line + 1) + " is: " + s1);
                    Console.WriteLine("s2 line " + (line + 1) + " is: " + s2);
                    Console.WriteLine(
                        );
                    equal = false;
                }
                ++line;
            }

            if (line < lengthe1)
            {
                int line1 = line;
                while (((s1 = r1.ReadLine()) != null))
                {
                    Console.WriteLine("s1 line " + (line1 + 1) + " is: " + s1);
                    ++line1;
                }
            }

            if (line < lengthe2)
            {
                int line2 = line;

                while (((s2 = r2.ReadLine()) != null))
                {
                    Console.WriteLine("s2 line " + (line2 + 1) + " is: " + s2);
                    ++line2;
                }
            }

            if (equal)
            {
                Console.WriteLine("Equalety");
            }


            Console.ReadKey();

        }


    }
}
