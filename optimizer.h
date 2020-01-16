#ifndef OPTIMIZE_H
#define OPTIMIZE_H

class path_optimization{
private:
    // Hold indices corresponding to start and end of contiguous parallel vector sets
    std::vector<int> starts, ends;
    // Holds the unoptimized path of orthogonal vectors
    std::vector<std::vector<int>> unoptimized_path;

    // Returns true if vector is vertical and false otherwise
    bool isvertical(const std::vector<int> v);
    // Finds the sum of a set of parallel vectors
    std::vector<int> parallel_vector_sum(const std::vector<std::vector<int>> v);
    // Finds where a set of parallel vectors begin and end and stores positions in corresponding vectors
    void run_finder();
    // Overloading of the addition operator that only adds orthogonal vectors. Returns a null vector otherwise
    friend std::vector<int> operator+(const std::vector<int> v1, const std::vector<int> v2);
    // Converts a vector of vectors into 2 distinct vectors of distances and headings
    result clean_up(std::vector<std::vector<int>> optimized);

public:
    // Constructor
    path_optimization(const std::vector<int> distances, const std::vector<char> headings);
    // Optimizes a given path by removing back tracks. Returns a struct containing direction and heading vectors
    result optimize();
};
#endif