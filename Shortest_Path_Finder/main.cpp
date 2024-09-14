#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
using namespace std;

void first_greeting(){
    cout << "\t\t\t\t------------------WELCOME TO SHORTEST PATH FINDER------------------" << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t Please take your map in your hand and Enter carefully" << endl;
    cout << "\t\t\t\t\t\t Refer your cities from 1 to total number of cities" << endl;
}

void last_greeting(){
    cout << "\t\t\t\tThank you for using SHORTEST PATH FINDER................" << endl << endl;
    cout << "\t\t\t\tHAVE A NICE DAY....." << endl;
}

void print_path(vector <int> &path,vector <int> &srt_path, int i){   // To print the map from source vertex to destination vertex
    if(path[i] == -1){
        return;
    }

    print_path(path,srt_path, path[i]);
    srt_path.push_back(i+1);
    cout << i + 1 << " ";
}

bool check_correct_city(int city, int total_cities){
    if(city > total_cities || city < 1)
        return false;
    return true;
}

bool check_correct_path(int city, vector <int> &srt_path){
    int l = 0, r = srt_path.size()-1;

    while(l <= r){
        int m = l + (r - l)/2;

        if(city == srt_path[m])
            return true;
        else if(srt_path[m] < city)
            l = m + 1;
        else
            r = m - 1;
    }
    return false;
}

void Shortest_Path_Finder(unordered_map <int, vector<pair<int, int>>> &adj, vector <int> &srt_path,int curr_location, int destination, int no_of_cities){

    vector <bool> vis(no_of_cities, false);
    vector <int> shortest_dis(no_of_cities, INT_MAX);
    vector <int> path(no_of_cities, -1);

    shortest_dis[curr_location - 1] = 0;

    for(int i = 0; i < no_of_cities; i++){

        int mini = INT_MAX, u = 0;
        for(int v = 0; v < no_of_cities; v++){
            if(vis[v] == false && shortest_dis[v] < mini){
                mini = shortest_dis[v];
                u = v;
            }
        }

        vis[u] = true;

        for(auto j: adj[u+1]){
            if(!vis[j.first -1] && j.second + shortest_dis[u] < shortest_dis[j.first - 1]){
                shortest_dis[j.first - 1] = shortest_dis[u] + j.second;
                path[j.first - 1] = u;
            }
        }
    }

    cout << "Shortest path from your location to destination: ";
    cout << curr_location << " ";
    srt_path.push_back(curr_location);
    print_path(path, srt_path, destination-1);
    cout << endl;
}

int main()
{
    first_greeting();
    int no_of_cities, total_path;
    cout << "Enter total numbers of cities: ";
    cin >> no_of_cities;
    cout << "Enter total numbers of paths in your map: ";
    cin >> total_path;

    unordered_map <int, vector<pair<int, int>>> adj;
    vector <int> srt_path;

    cout << "Enter your Map:" << endl;
    cout << "Enter your first city and press space, enter your second city and press space, enter distance between these two cities:" << endl;
    for(int i = 0; i < total_path; i++){
        int first, second, distance;
        cin >> first >> second >> distance;
        adj[first].push_back({second, distance});
        adj[second].push_back({first, distance});
    }
    int curr_location;
    while(1){
        cout << "Enter your current location among your entered cities: ";
        cin >> curr_location;
        if(check_correct_city(curr_location, no_of_cities))
            break;
        cout << "INVALID INPUT, ENTER AGAIN" << endl;
    }
    int destination;
    while(1){
        cout << "Enter your destination location among your entered cities: ";
        cin >> destination;
        if(check_correct_city(destination, no_of_cities))
            break;
        cout << "INVALID INPUT, ENTER AGAIN" << endl;
    }

    Shortest_Path_Finder(adj,srt_path, curr_location, destination, no_of_cities);

    cout << "Do you want to travel(Yes/No): ";
    string answer;
    cin >> answer;

    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    if(answer == "no"){
        last_greeting();
        return 0;
    }

    int location = -1;
    while(1){

        while(1){
            cout << "Enter your current location among your entered cities: ";
            cin >> location;
            if(check_correct_city(location, no_of_cities))
                break;
            cout << "INVALID INPUT, ENTER AGAIN" << endl;
        }
        if(!check_correct_path(location, srt_path)){
            cout << "You lost your shortest path " << endl << endl;
            cout << "Do you want to change your destination(Yes/No): ";
            string answer1;
            cin >> answer1;
            transform(answer1.begin(), answer1.end(), answer1.begin(), ::tolower);
            if(answer1 == "yes"){
                while(1){
                    cout << "Enter your new destination location: ";
                    cin >> destination;
                    if(check_correct_city(destination, no_of_cities))
                        break;
                    cout << "INVALID INPUT, ENTER AGAIN" << endl;
                }
            }
            srt_path.clear();
        }

        if(location == destination){
            last_greeting();
            return 0;
        }
        Shortest_Path_Finder(adj, srt_path, location, destination, no_of_cities);
    }


    return 0;
}
