#include <iostream>
#include <string>
#include <unistd.h>
#include "../lib/EZProgressBar.h"

using namespace std;

int main()
{
    int n = 10;
    ez::EZProgressBar eta;
    eta = ez::EZProgressBar(10);

    eta.start();
    for(int i = 0; i <= n; ++i, ++eta)
    {
        sleep(1);
    }
}

// #include <iostream>
// #include <string>
// #include <cstdio>
// #include <iomanip>
//
// using namespace std;
//
// static inline void loadbar(unsigned int x, unsigned int n, unsigned int w = 50)
// {
//     if ( (x != n) && (x % (n/100+1) != 0) ) return;
//
//     float ratio  =  x/(float)n;
//     int   c      =  ratio * w;
//
//     cout << setw(3) << (int)(ratio*100) << "% [";
//     for (int x=0; x<c; x++) cout << "=";
//     for (int x=c; x<w; x++) cout << " ";
//     cout << "]\r" << flush;
// }
//
// int main()
// {
//     for (int i = 0; i < 100; i++)
//     {
//         loadbar(i+1,100);
//     }
// 	return 0;
// }
// #include <boost/progress.hpp>
// #include <boost/timer.hpp>
// #include <vector>
//
// int main(int argc,char *argv[])
// {
//     const unsigned long expected_count=20;
//     boost::progress_display show_progress( expected_count );
//     for(int i=0;i!=expected_count;++i)
//     {
//         volatile std::vector<int> v(1024*1024*128);
//         ++show_progress;
//     }
//     return 0;
// }
// A simple c++ progress bar dumped in the terminal



// class ProgressBar
// {
// public:
//
//   ProgressBar(unsigned int max, std::string message = std::string("")) :
//     _max(max), _progress(0), _counter(0), _message(message),
//     _bar(50, ' ')
//   {
//     _bar[0] = '#';
//   }
//
//   ~ProgressBar()
//   {
//     std::cout << std::endl;
//   }
//
//   void progress()
//   {
//     unsigned int currentProgress = (_counter*100)/(_max - 1);
//
//     if (_progress < currentProgress)
//     {
//       _progress = currentProgress;
//
//       std::fill_n(_bar.begin(), _progress/2, '#');
//
//       std::cout << "\r" << _message << "  [" << _bar << "] "
//                 << _progress << "%" << std::flush;
//     }
//
//     ++_counter;
//   }
//
//   void operator++()
//   {
//     progress();
//   }
//
//   void operator++(int)
//   {
//     progress();
//   }
//
// protected:
//
//   unsigned int _max;
//   unsigned int _progress;
//   unsigned int _counter;
//
//   std::string _message;
//   std::string _bar;
// };

// int main()
// {
//   int max_it = 5000;
//   ProgressBar pb(max_it, "Progress");
//
//   for (int i=0; i<max_it; ++i, ++pb)
//   {
//     // std::vector<int> v(1024*1024);
//   }
//
//   return 0;
// }

// #include <iostream>
// #include <string>
// #include "ProgressBar.h"
//
// using namespace std;
//
// int main()
// {
//     pb::ProgressBar progressBar(100);
//     // std::chrono::milliseconds duration(200);
//
//     for (int i = 0; i < 101; ++i)
//     {
//         std::vector<int> v(100000);
//         cout << "Here" << endl;
//         progressBar.update(i);
//         // std::this_thread::sleep_for(duration);
//     }
// }
