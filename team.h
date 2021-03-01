#include<bits/stdc++.h>
#include "player.h"
using namespace std;
class Team {
	int id;
	vector<Player> players; // players with given batting order
	int striker_index, non_striker_index, next_batsman_index, team_extras, team_total, wickets_fall, total_legal_delivery;
public:
	void set_batting_order(vector<Player> batting_order){
		this->players = batting_order;
		// size should be greater than 1
		this->striker_index = 0;
		this->non_striker_index = 1;
		this->next_batsman_index = 2;
		this->team_extras = 0;
		this->team_total = 0;
		this->wickets_fall = 0;
		this->total_legal_delivery = 0;
	}

	int get_striker_index(){
		return this->striker_index;
	}

	void change_striker(){
		swap(this->striker_index, this->non_striker_index);
	}

	void increment_total_legal_delivery()
	{
		(this->total_legal_delivery) += 1;
	}

	void increment_team_total(int run_scored)
	{
		this->team_total += run_scored;
	}

	void process_ball(string action_performed_on_a_ball, bool is_no_ball = false){
		int run_scored = (char)action_performed_on_a_ball[0] - '0';
		int striker_index = get_striker_index();
		increment_team_total(run_scored);

		if(!is_no_ball)   // if not a no ball then incrment legal delivery otherwise increment player's run & ball faced
			increment_total_legal_delivery();

		players[striker_index].increment_run_count(run_scored);
		players[striker_index].increment_ball_faced();
		if(run_scored % 2){
			change_striker();
		}
	}

	void process_out(){
		int striker_index = get_striker_index();
		players[striker_index].increment_ball_faced();
		this->striker_index = this->next_batsman_index;
		(this->next_batsman_index) += 1;
		(this->wickets_fall) += 1;
		(this->total_legal_delivery) += 1;
	}

	int wickets_in_hands()
	{
		return (this->players.size() - this->wickets_fall - 1);
	}

	bool is_all_out()
	{
		return (wickets_in_hands() <= 0);
	}

	bool whether_player_not_out(int index)
	{
		if(index == this->striker_index || index == this->non_striker_index) {
			return true;
		}

		return false;
	}

	int get_team_total()
	{
		return this->team_total;
	}


	void increment_extras(string action_performed_on_a_ball, bool whether_change_striker = false){
		int run_scored = (char)action_performed_on_a_ball[0] - '0';
		(this->team_extras) += run_scored;
		(this->team_total) += run_scored;
		if(whether_change_striker && run_scored % 2) {
			change_striker();
		}
	}

	void print_summary(){
		cout<<"Player Name\t Score\t 4s\t 6s\t Balls\t Strike rate\n";

		for(int i=0;i<players.size();i++)
		{
			cout << players[i].get_id() << (whether_player_not_out(i) ? "*" : "") << "\t\t " << players[i].get_run_scored() << "\t " << players[i].get_no_of_4s() << "\t "<< players[i].get_no_of_6s() << "\t " << players[i].get_ball_faced()<< "\t "<< players[i].get_strike_rate()<<"\n";
		}

		cout<<"Total: " << this->team_total << "/" << this->wickets_fall << "\n";
		cout<<"Overs: "<<this->total_legal_delivery/6<<"."<<this->total_legal_delivery%6<<"\n";
		cout<<"Team Extras: " << this->team_extras<<"\n";
	}

	pair<float,string> calculate_max_point(int max_run_scored_including_both_team)
	{
		float max_point_collected_by_player = ((float)players[0].get_run_scored()/max_run_scored_including_both_team);
		string Player_id = players[0].get_id();
		for(int i=1;i<players.size();i++)
		{
			float current_point_collected_by_player = ((float)players[i].get_run_scored()/max_run_scored_including_both_team);
			if(current_point_collected_by_player > max_point_collected_by_player)
			{
				max_point_collected_by_player = current_point_collected_by_player;
				Player_id = players[i].get_id();
			}
		}

		return {max_point_collected_by_player, Player_id};
	}


	// 5/20 -> 25% (2.5)   1 point for 10% of max/min(run_scored_by_tea1_or_team2)
	// 6/20 -> 30% (3)	
	// 4/20 -> 20% (2)
	// 3/20 -> 15% (1.5)
	// 1/20 -> 5%  (0.5)
	// 6/20 15

	
};