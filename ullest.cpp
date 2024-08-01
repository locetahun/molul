#include <iostream>
#include <vector>

int compute_sum(const std::vector<int>& numbers);

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int total_sum = compute_sum(nums);
    
    std::cout << "Sum of numbers: " << total_sum << std::endl;
    
    return 0;
}
