#include <iostream>
#include <vector>
#include "result.h"
#include "optimizer.h"

int main(){
}

std::vector<int> operator+(const std::vector<int> v1, const std::vector<int> v2){
    // Consider x-components
    int x1 = v1[0];
    int x2 = v2[0];
    // Consider y-components
    int y1 = v1[1];
    int y2 = v2[1];
    // Instantiate return object
    std::vector<int> ret;
    if(x1 == 0 && x2 == 0 || y1 ==0 && y2 ==0){
        ret.push_back(x1+x2);
        ret.push_back(y1+y2);
    }
    // return an empty vector if vectors cannot be added
    return ret;
}

bool path_optimization::isvertical(const std::vector<int> v){
    // the zero vector is not vertical
    if(v[1] != 0 && v[0] == 0){
        return true;
    }
    return false;
}

std::vector<int> path_optimization::parallel_vector_sum(const std::vector<std::vector<int>> v){
    // only consider all in the same direction
    int size = v.size();
    std::vector<int> sum = {0,0};
    for (int i = 0; i < size; i++)
    {
        sum = sum + v[i];
    }
    return sum;
}

void path_optimization::run_finder(){
    int subject_size = unoptimized_path.size();
    bool vertical;
    starts.push_back(0);
    vertical = isvertical(unoptimized_path[0]);
    for(int i = 1; i<subject_size; i++){
        if (isvertical(unoptimized_path[i]) != vertical){
            starts.push_back(i);
            ends.push_back(i-1);
            vertical = !vertical;
        }
    }
    ends.push_back(subject_size-1);
}

path_optimization::path_optimization(const std::vector<int> raw_distances, const std::vector<char> raw_headings){
    // Parse the specified vectors and consolidate into a single vector composed of vectors named unoptimized_path
    for(int i = 0; i<raw_distances.size(); i++){
        if (raw_headings[i] == 'E'){
            unoptimized_path.push_back({raw_distances[i], 0});
        }
        else if(raw_headings[i] == 'W'){
            unoptimized_path.push_back({-raw_distances[i], 0});
        }
        else if(raw_headings[i] == 'N'){
            unoptimized_path.push_back({0,raw_distances[i]});
        }
        else{
            unoptimized_path.push_back({0,-raw_distances[i]});
        }
    }
    // Populate ends and starts member variables now that unoptimized_path contains the necessary data 
    run_finder();
}

// Converts a vector of vectors into 2 distinct vectors of distances and headings. Returns a struct
result path_optimization::clean_up(std::vector<std::vector<int>> optimized){
    result ret;
    for(int i = 0; i<optimized.size(); i++){
        if(isvertical(optimized[i])){
            ret.distances.push_back(abs(optimized[i][1]));
            if(optimized[i][1]>=0){
                ret.headings.push_back('N');
            }
            else{
                ret.headings.push_back('S');
            }
        }
        else{
            ret.distances.push_back(abs(optimized[i][0]));
            if(optimized[i][0] >= 0){
                ret.headings.push_back('E');
            }
            else{
                ret.headings.push_back('W');
            }
        }
    }
    return ret;
}

// Optimizes the path by eliminating back-tracks
result path_optimization::optimize(){
    std::vector<std::vector<int>> ret;
    for(int i = 0; i<starts.size(); i++){
        std::vector<int> v = parallel_vector_sum(std::vector<std::vector<int>>(unoptimized_path.begin()+starts[i], unoptimized_path.begin()+ends[i]+1));
        // Do not include the 0 vector:
        if(v[0] || v[1]){
            ret.push_back(v);
        }
    }
    // Now the unoptized path becomes the optimized path
    unoptimized_path = ret;
    return clean_up(ret);
}