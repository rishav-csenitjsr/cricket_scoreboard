#include<bits/stdc++.h>
#include "cricket_match.h"
using namespace std;
class Main {

public:
 void execute(){

 	int total_players_in_teams, no_of_overs, result_declared = 0;
	vector<string> pid;
	string player_id;
	cout<<"*******************\n";
	Match match;
	cout<<"No. of players for each team: \n";
	cin>>total_players_in_teams;

	// bare min condition
	if(total_players_in_teams < 2)
	{
		cout<< "You choose very few number of players for each team. Please try again with value >= 2 !!!!";
		exit(0);
	}
	match.set_number_of_players(total_players_in_teams);
	cout<<"No. of overs: \n";
	cin>>no_of_overs;
	if(no_of_overs <= 0)
	{
		cout<< "You have given wrong input for 'Number of Overs to be bowled'. Please try again with value >= 1 !!!!";
		exit(0);
	}

	match.set_number_of_overs(no_of_overs);
	cout<<"Batting Order for team 1: \n";
	for(int i=0;i<total_players_in_teams; i++){
		cin>>player_id;
		pid.push_back(player_id);
	}
	match.set_batting_order(1, pid);

	for(int i = 1; i<= no_of_overs; i++){
		cout<< "Over " << i << ": \n";
		int is_team_got_all_out_in_current_over = match.process_over(i, 1); // 0 -> team doesn't got out, 1 -> team got all out
		cout<<"Scorecard for Team 1:\n";
		match.print_over_summary(i, 1);
		
		if(is_team_got_all_out_in_current_over)
			break;

	}
	pid.clear();
	cout<<"Batting Order for team 2: \n";
	for(int i=0;i<total_players_in_teams; i++){
		cin>>player_id;
		pid.push_back(player_id);
	}

	match.set_batting_order(2, pid);
	for(int i = 1; i<= no_of_overs; i++){
		cout<< "Over " << i << ": \n";
		int over_response = match.process_over(i, 2); // 0 -> team doesn't got out, 1 -> team got all out, 2 -> team won
		cout<<"Scorecard for Team 2:\n";
		match.print_over_summary(i, 2);
		if(over_response > 0)
		{
			match.print_result();
			result_declared = 1;
			break;
		}
	}

	if(!result_declared)
	{
		match.print_result();
	}
 }

};

int main()
{
	Main action;
	action.execute();

	return 0;

}



