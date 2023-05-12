//zoom size 125%

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<functional>
#include<chrono>
#include<random>
using namespace std;

struct Movie {
  int id;
  bool bought;
    Movie (int id):id (id), bought (false) {}
};

class MovieThreater {
    private:
    vector < thread > workers_;
   queue < function < void () >> tasks_;
   mutex mutex_;
   condition_variable condition_;
   bool stop_ = false;
public:
  MovieThreater (size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
	workers_.emplace_back ([this] {
			       while (true) {
			       function < void () > task; {
			       unique_lock < mutex > lock (mutex_);
			       condition_.wait (lock,[this] {
						return stop_|| !tasks_.empty ();});
						if (stop_ && tasks_.empty ()){
			       return;
						}
			       task = move (tasks_.front ()); tasks_.pop ();}
			       task ();}
			       }
	);
    }
  }
  
  ~MovieThreater (){
    {
      unique_lock < mutex > lock (mutex_);
      stop_ = true;
    }
    condition_.notify_all ();
  for (thread & worker:workers_)
      {
	worker.join ();
      }
  }
  
  void enqueue (shared_ptr < Movie > movie)
  {
    {
      unique_lock < mutex > lock (mutex_);
      tasks_.emplace ([movie, this]
		      {
		      const char *m[3] = {"AVENGERS", "SPIDERMAN", "JOKER"};
		      int in = rand () % 3;
		      int t = rand () % 5 + 1;
		      this_thread::sleep_for (chrono::seconds (t));
		      movie->bought = true;
		      int c = 1;
		      while (c != 0)
		      {
		      cout << "New customer arrived { Movie : " << m[in] << " , Quantity : " << t << " , Arrival Time : " << t +5 << " , Customer ID : " << movie->id << " }" << endl << endl;
		      cout << "Customer " << movie->id << " | Bought " << t << " " << m[in] << " tickets for " << t *200 << " Rs at time " << t +5 << " :)" << endl << endl << endl; c--;}
		      }
      );
    }
    
    
    condition_.notify_one ();
    
  }
};

int main () {
  int customers=12, counters=1, total_sales=0;
  float avg=0.00;
  string ans;
  cout << "\t\t\t\t\t\t____________________________\n\n";
  cout << "\t\t\t\t\t\t  WELCOME TO TICKET BOOTH\n";
  cout << "\t\t\t\t\t\t____________________________\n\n\n";
  cout << "Today's show and their timings are:\n\n";
  cout << "1. AVENGERS 4:15PM , AUDI 4\n\n";
  cout << "2. SPIDERMAN 5:30PM , AUDI 1\n\n";
  cout << "3. JOKER 6:00PM , AUDI 3\n\n\n";
  cout << "---------------------------------------------------------------------------------------------------------------------------------\n";
  cout << "\n\nDo you want to move towards ticket counter?\n-> Yes                       -> No\n\n\n";
  cin >> ans;
  cout << "\n--------------------------------------------------------------------------------------------------------------------------------\n\n";
  if (ans == "Yes" or ans == "yes" or ans == "YES") {
      cout << "                                                 ........................\n\n";
      cout << "                                                        MOVIES LIST\n\n";
      cout << "                                                 ........................\n\n\n";
      cout << "@ AVENGERS  200 INR                                 @ SPIDERMAN 200 INR                                    @ JOKER 200 INR\n\n";
      cout << "\n---------------------------------------------------------------------------------------------------------------------------------\n\n\n";
      
      struct tm *ptr;
      time_t t;
      t = time (NULL);
      ptr = localtime (&t);
      cout << endl << endl << "\t\t\t\t\t\t\t\t\t\t\t\t" << asctime (ptr) << endl << endl << endl;

      MovieThreater threater (4);
      vector < shared_ptr < Movie >> mov;
      for (int i = 0; i < customers; ++i)
	{
	  mov.push_back (make_shared < Movie > (i));
	}
    for (auto & movie:mov)
	{
	  threater.enqueue (movie);
	}
      bool all_bought = false;
      while (!all_bought)
	{
	  this_thread::sleep_for (chrono::milliseconds (100));
	  all_bought = true;
	for (const auto & movie:mov)
	    {
	      if (!movie->bought)
		{
		  all_bought = false;
		  break;
		}
	    }
	}
	
	
	for(int j=0;j<customers; j++){
	    total_sales+=( rand () % 5 + 1) * 200;
	}
	avg=(float)total_sales/customers;
	
	
	cout<<"\n---------------------------------------------------------------------------------------------------------------------------------\n\n\n";
    cout<<"\n************************************************\n\n";
    cout<<"         TICKET WINDOW SALES INSIGHTS\n\n";
    cout<<"************************************************\n\n";
    cout << "  (All tickets are sold out)" <<endl<<endl;
    cout<<"-> No. of ticket counters :- "<<counters<<endl<<endl;
    cout<<"-> No. of customers :- "<<customers<<endl<<endl;
    cout<<"-> Total sales :- "<<total_sales<<" INR \n\n";
    cout<<"-> Avg. sales per customer :- "<<(float)avg<<" INR\n\n";
    }
}


