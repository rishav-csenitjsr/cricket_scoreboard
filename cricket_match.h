#include<bits/stdc++.h>

#include "team.h"

using namespace std;

class Match {
	int number_of_players, number_of_overs;
	Team team_1, team_2, current_team;
public:
	void set_number_of_players(int player_count){
		number_of_players = player_count;
	}

	void set_number_of_overs(int overs_count){
		number_of_overs = overs_count;
	}

	void set_batting_order(int team_id, vector<string> batting_order){
		vector<Player> total_palyers_in_a_team;
		for(int i =0;i< batting_order.size();i++)
		{
			Player player(batting_order[i]);
			total_palyers_in_a_team.push_back(player);
		}
		if(team_id == 1) {
			team_1.set_batting_order(total_palyers_in_a_team);
		} else {
			team_2.set_batting_order(total_palyers_in_a_team);
		}

	}

	bool check_for_legal_delivery(string action_on_ball_faced) {
		if(action_on_ball_faced.size() > 1) {
			return false;
		}

		return true;
	}

	bool is_team_not_won(int team_id)
	{
		if(team_id == 1)
			return true;
		else {
			return (current_team.get_team_total() <= team_1.get_team_total());
		}
	}

	bool process_over(int over_number, int team_id){
		int ball_faced_in_a_over = 0;
		bool is_legal_delivery;
		int over_response = 0;  // 0 -> team doesn't got out, 1 -> team got all out, 2 -> team won

		current_team = (team_id == 1 ? team_1 : team_2);
		string action_on_ball_faced;
		for(; (ball_faced_in_a_over < 6 && !current_team.is_all_out()); ) {
			cin>>action_on_ball_faced;

			is_legal_delivery = check_for_legal_delivery(action_on_ball_faced);

			if(is_legal_delivery) {	
				ball_faced_in_a_over++;
				if(action_on_ball_faced[0] >= '0' && action_on_ball_faced[0] <= '6')
				{
					current_team.process_ball(action_on_ball_faced);
				} else if(action_on_ball_faced == "W") {
					current_team.process_out();
				}
			} else if(action_on_ball_faced[0] == 'W') {
				current_team.increment_extras("1");
			} else if(action_on_ball_faced[1] == 'W') {             // this is the case of Wide
				current_team.increment_extras(action_on_ball_faced);
			} else if(action_on_ball_faced[1] == 'N') {												// this is the case of No-ball
				current_team.increment_extras("1");
				current_team.process_ball(action_on_ball_faced, true);
			} else {
				cout<< "You entered Wide or No ball delivery in incorrect way. please try again in format 'Wd, 1Wd, 2Wd or 0N, 1N' etc... Please try again..!!";
				continue;
			}


			if(!is_team_not_won(team_id)) {
				over_response = 2;
				break;
			}

		}

		if(over_response == 0) {
			if(!current_team.is_all_out()) {	
				current_team.change_striker();
				over_response = 0;
			} else if( current_team.is_all_out()) {
				over_response = 1;
			}
		}
		
		
		if(team_id == 1)
			team_1 = current_team;
		else
			team_2 = current_team;

		return over_response;

	}

	void print_over_summary(int over_number, int team_id){
		current_team.print_summary();
	}

	void print_result()
	{
		if(team_1.get_team_total() == team_2.get_team_total())
		{
			cout<<"Match Draw!!!!\n";
		} else if(team_1.get_team_total() > team_2.get_team_total())
		{
			cout<<"Team 1 won the match by "<< (team_1.get_team_total() - team_2.get_team_total()) <<" runs\n";
		} else {
			cout<< "Team 2 won the match with "<< team_2.wickets_in_hands() << " wickets in hand\n";
		}
	}

};
