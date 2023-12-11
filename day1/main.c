#include "main.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct split_string_t {
  char *first;
  char *second;
} split_string_t;

int split(const char *str, const char *delimiter, split_string_t *ss) {
  char *delimiterPosition = strstr(str, delimiter);
  if (delimiterPosition ==
      NULL) { // this means the delimiter is not found in the string
    return -1;
  }
  // length of the first part including the delimiter
  size_t firstPartLength = delimiterPosition - str + strlen(delimiter);
  ss->first = malloc(firstPartLength + 1);
  ss->second = malloc(strlen(delimiterPosition + strlen(delimiter)) + 1);
  strncpy(ss->first, str, firstPartLength);
  ss->first[firstPartLength] = '\0';
  strcpy(ss->second, delimiterPosition + strlen(delimiter));
  return 0;
}

void reverse_string(const char *str, int strlength, char *hold) {
  int j = 0;
  for (int i = strlength - 1; i >= 0; i--) {
    hold[j] = str[i];
    j++;
  }
  hold[strlength] = '\0';
}

int process_line(char *line, int length) {
  int first;
  int last;
  for (int i = 0; line[i]; i++) {
    if (isdigit(line[i])) {
      first = (int)line[i] - '0';
      break;
    }
  }

  // looping from back
  for (int i = length; i >= 0; i--) {

    if (isdigit(line[i])) {
      last = (int)line[i] - '0';
      break;
    }
  }

  // Converting two digits into a new number

  char number[1024];
  snprintf(number, 1024, "%d%d", first, last);
  return atoi(number);
}

char *digits[9] = {
    [0] = "one", [1] = "two",   [2] = "three", [3] = "four", [4] = "five",
    [5] = "six", [6] = "seven", [7] = "eight", [8] = "nine",

};

char *rev_digits[9] = {
    [0] = "eno", [1] = "owt",   [2] = "eerht", [3] = "ruof", [4] = "evif",
    [5] = "xis", [6] = "neves", [7] = "thgie", [8] = "enin",

};

int find_first_digit(char *str) {
  for (int i = 0; str[i]; i++) {
    if (isdigit(str[i])) {
      return (int)str[i] - '0';
    }
  }
  return -1;
}

int first_digit_recurse(char *str, int current_count) {
  split_string_t *ss;
  ss = (split_string_t *)malloc(sizeof(split_string_t));
  if (current_count < 9) {
    int result = split(str, digits[current_count], ss);
    if (result != -1) {
      if (strcmp(ss->first, digits[current_count]) == 0) {
        return current_count + 1;
      } else {
        int sub = first_digit_recurse(ss->first, current_count + 1);
        if (sub == -1) {
          int first_digit = find_first_digit(ss->first);
          if (first_digit != -1) {
            return first_digit;
          }
          return current_count + 1;
        }
        return sub;
      }
    } else {
      return first_digit_recurse(str, current_count + 1);
    }
  }
  return find_first_digit(str);
}

int last_digit_recurse(char *str, int current_count) {
  split_string_t *ss;
  ss = (split_string_t *)malloc(sizeof(split_string_t));
  if (current_count < 9) {
    int result = split(str, rev_digits[current_count], ss);
    if (result != -1) {
      if (strcmp(ss->first, rev_digits[current_count]) == 0) {
        return current_count + 1;
      } else {
        int sub = last_digit_recurse(ss->first, current_count + 1);
        if (sub == -1) {
          int first_digit = find_first_digit(ss->first);
          if (first_digit != -1) {
            return first_digit;
          }
          return current_count + 1;
        }
        return sub;
      }
    } else {
      return last_digit_recurse(str, current_count + 1);
    }
  }
  return find_first_digit(str);
}

int part_deu(char *line, int length) {

  split_string_t *ss;
  int first = 0;
  int second = 0;
  char reversed_string[length];
  char combined_num[20];
  first = first_digit_recurse(line, 0);
  reverse_string(line, length, reversed_string);
  second = last_digit_recurse(reversed_string, 0);
  sprintf(combined_num, "%d%d", first, second);
  int num = atoi(combined_num);
  return num;
}

int main() {

  printf("Day One Homie!\n");

  // READING THE FILE
  FILE *file = fopen("input.txt", "r");

  if (file == NULL) {
    perror("Error reading the input!\n");
    return -1;
  }
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int sum = 0;
  int sum2 = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    // do stuff only when line is not empty
    sum += process_line(line, strlen(line));
    sum2 += part_deu(line, strlen(line));
    //	printf("%s", line);
  }
  printf("Part One %d\t Part Two %d\n", sum, sum2);

  // END OF READING FILE

  return 0;
}
