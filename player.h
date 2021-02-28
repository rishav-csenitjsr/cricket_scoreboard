#include<bits/stdc++.h>
using namespace std;

class Player {

	string id;
	int run_scored;
	int ball_faced;
	int wicket_taken;
	int economy;
	int balls_bowled;
	int no_of_4s;
	int no_of_6s;
public:
	Player(string id){
		this->id = id;
		this -> run_scored = this->ball_faced = this->wicket_taken = this->economy = this->balls_bowled = this->no_of_6s = this->no_of_4s = 0;
	}

	void increment_ball_faced()
	{
		this->ball_faced++;
	}

	void increment_run_count(int run_scored){
		this->run_scored += run_scored;
		if(run_scored == 4)
		{
			this->no_of_4s+=1;
		} else if(run_scored == 6)
		{
			this->no_of_6s+=1;
		}
	}

	string get_id()
	{
		return this->id;
	}

	int get_run_scored()
	{
		return this->run_scored;
	}

	int get_ball_faced()
	{
		return this->ball_faced;
	}

	int get_wicket_taken()
	{
		return this->wicket_taken;
	}

	int get_balls_bowled()
	{
		return this->balls_bowled;
	}

	int get_no_of_4s()
	{
		return this->no_of_4s;
	}

	int get_no_of_6s()
	{
		return this->no_of_6s;
	}

	float get_strike_rate()
	{
		if(this->run_scored == 0)
			return 0.00;
		else
		{
			return ((float) this->run_scored / (this->ball_faced))*100;
		}
	}
	
};