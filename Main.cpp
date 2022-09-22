#include <iostream>
#include <string>
#include <vector>
#include <chrono>

uint64_t compute_subsquences(
    const std::string_view first_string,
    const std::string_view second_string)
{
  uint64_t first_string_length = first_string.length();
  uint64_t second_string_length = second_string.length();
  uint64_t lookup_matrix[first_string_length + 1][second_string_length + 1] = {{0}};
  for (uint64_t i = 0; i <= second_string_length; ++i)
    lookup_matrix[0][i] = 0;
  for (uint64_t i = 0; i <= first_string_length; ++i)
    lookup_matrix[i][0] = 1;
  for (uint64_t i = 1; i <= first_string_length; ++i)
    for (uint64_t j = 1; j <= second_string_length; ++j)
      if (first_string[i - 1] == second_string[j - 1])
        lookup_matrix[i][j] = lookup_matrix[i - 1][j - 1] + lookup_matrix[i - 1][j];
      else
        lookup_matrix[i][j] = lookup_matrix[i - 1][j];
  return lookup_matrix[first_string_length][second_string_length];
}

auto main(int32_t argc, char const *argv[]) -> int32_t
{
  std::string test_cases;

  std::cout << "How many test cases? ";
  std::getline(std::cin, test_cases);

  for (uint32_t i = 0; i < std::atoi(test_cases.c_str()); ++i)
  {
    std::putchar(10);
    std::string sentence, text;

    std::cout << "Text: ";
    std::getline(std::cin, text);

    std::cout << "Sentence: ";
    std::getline(std::cin, sentence);

    auto start_time = std::chrono::high_resolution_clock::now();
    uint32_t subsquences = compute_subsquences(text, sentence);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "-- Output: " << subsquences << std::endl;
    std::cout << "-- Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;
  }

  return EXIT_SUCCESS;
}
