#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using std::boolalpha;
using std::cin;
using std::cout;
using std::deque;
using std::map;
using std::max;
using std::multimap;
using std::multiset;
using std::pair;
using std::queue;
using std::set;
using std::stack;
using std::string;
using std::vector;

struct SumOfLastKNumbers {
  int k = 0;
  int sum = 0;
  queue<int> q;

  SumOfLastKNumbers(int k) { this->k = k; }

  int next(int newNum) {
    this->q.push(newNum);
    this->sum += newNum;

    if ((int)q.size() > k) {
      this->sum -= q.front();
      this->q.pop();
    }

    return sum;
  }
};

bool validParentheses(string str) {
  map<char, char> m;
  m[')'] = '(';
  m[']'] = '[';
  m['}'] = '{';

  stack<char> s;

  for (char item : str) {
    if (m.count(item)) {
      if (s.empty()) {
        return false;
      }

      char open = m[item];
      char currentOpen = s.top();

      if (open != currentOpen) {
        return false;
      }

      s.pop();
    } else {
      s.push(item);
    }
  }
  return s.empty();
}

void readQuery(const map<string, vector<string>>& mp) {
  int q;
  cout << "Enter number of queries: ";
  cin >> q;

  while (q--) {
    int len;
    cout << "Enter length of name to read: ";
    cin >> len;

    string str = "";
    string currentFullName = "";

    for (int j = 0; j < len; j++) {
      cout << "Enter name: ";
      cin >> str;

      if (j) {
        currentFullName += " ";
      }

      currentFullName += str;
    }

    if (mp.count(currentFullName)) {
      for (string str : mp.at(currentFullName)) {
        cout << str << "\n";
      }
    } else {
      cout << "No such sub-fullname.\n";
    }
  }
}

void findFullNames() {
  int n;
  map<string, vector<string>> mp;

  cout << "Enter the number of entries: ";
  cin >> n;

  for (int i = 0; i < n; i++) {
    int len;
    cout << "Enter the length of name: ";
    cin >> len;

    string currentFullName = "";
    string str = "";
    vector<string> names;

    for (int j = 0; j < len; j++) {
      cout << "Enter name: ";
      cin >> str;

      if (j) {
        currentFullName += " ";
      }

      currentFullName += str;
      // names: mostafa, mostafa saad, mostafa saad ibrahem
      names.push_back(currentFullName);
    }

    for (auto str : names) {
      mp[str].push_back(currentFullName);
    }
  }

  readQuery(mp);
}

int sumVector(const vector<int>& v) {
  int sum = 0;
  vector<int>::const_iterator it = v.cbegin();

  while (it != v.cend()) {
    sum += *it;
    it++;
  }

  return sum;
}

int max3StacksSum(vector<int>& vector1, vector<int>& vector2, vector<int>& vector3) {
  int vectorSum1 = sumVector(vector1);
  int vectorSum2 = sumVector(vector2);
  int vectorSum3 = sumVector(vector3);

  while (!vector1.empty() && !vector2.empty() && !vector3.empty()) {
    if (vectorSum1 == vectorSum2 && vectorSum2 == vectorSum3) {
      return vectorSum1;
    }

    if (vectorSum1 >= vectorSum2 && vectorSum1 >= vectorSum3) {
      vectorSum1 -= vector1.back();
      vector1.pop_back();
    } else if (vectorSum2 >= vectorSum1 && vectorSum2 >= vectorSum3) {
      vectorSum2 -= vector2.back();
      vector2.pop_back();
    } else {
      vectorSum3 -= vector3.back();
      vector3.pop_back();
    }
  }

  return 0;
}

int slidingWindowV1() {
  int size = 7;
  int k = 3;

  int arr[size] = {1, 2, 3, 4, 5, 6, 7};

  int maxSum = 0;

  for (int i = 0; i < k; i++) {
    maxSum += arr[i];
  }

  for (int i = 1; i < size - k + 1; i++) {
    int roundSum = 0;

    for (int win = i; win < i + k; win++) {
      roundSum += arr[win];
    }

    if (maxSum < roundSum) {
      maxSum = roundSum;
    }
  }

  return maxSum;
}

int slidingWindowV2() {
  int size = 7;
  int k = 3;

  int arr[size] = {1, 2, 3, 4, 5, 6, 7};

  int maxSum = 0;

  for (int i = 0; i < k; i++) {
    maxSum += arr[i];
  }

  int roundSum = maxSum;

  for (int i = 1; i < size - k + 1; i++) {
    roundSum = roundSum - arr[i - 1] + arr[i + k - 1];

    maxSum = max(roundSum, maxSum);
  }

  return maxSum;
}

vector<int> slidingWindowV3(vector<int>& nums, int k) {
  vector<int> ret;

  if ((int)nums.size() < k) {
    return ret;
  }

  multiset<int> ms;

  for (int i = 0; i < k; i++) {
    ms.insert(-nums[i]);
  }

  ret.push_back(-(*ms.begin()));

  for (int i = k; i < (int)nums.size(); i++) {
    ms.erase(ms.find(-nums[i - k]));
    ms.insert(-nums[i]);
    ret.push_back(-(*ms.begin()));
  }

  return ret;
}

void reverseQueue(queue<int>& q) {
  stack<int> myStack;

  while (!q.empty()) {
    myStack.push(q.front());
    q.pop();
  }

  while (!myStack.empty()) {
    q.push(myStack.top());
    myStack.pop();
  }
}

struct MyStack {
  queue<int> q;

  // q: 1, 2, 3 add 7 to q to be 1, 2, 3, 7
  // because we need to push it in the front
  // will push the front of the stack at the end of it
  void push(int value) {
    int size = q.size();
    q.push(value);

    while (size--) {
      q.push(q.front());
      q.pop();
    }
  }

  void pop() {
    if (!q.empty()) {
      q.pop();
    }
  }

  int top() { return q.front(); }

  bool empty() { return q.empty(); }
};

// 12345
int reverseNumber(int num) {
  stack<int> s;

  while (num) {
    s.push(num % 10);  // q: 54321
    num /= 10;
  }

  int tens = 1;

  while (!s.empty()) {
    num = s.top() * tens + num;
    tens *= 10;
    s.pop();
  }

  return num;
}

void allWordsPrefix() {
  map<string, vector<string>> mp;

  int n;

  cout << "Enter number of entries: ";
  cin >> n;

  while (n--) {
    string str;

    cout << "Enter name: ";
    cin >> str;

    string current = "";

    for (int i = 0; i < (int)str.size(); i++) {
      current += str[i];
      mp[current].push_back(str);
    }
  }

  cout << "Enter number of queries: ";
  cin >> n;

  while (n--) {
    string str;

    cout << "Enter prefix: ";
    cin >> str;

    for (auto cur : mp[str]) {
      cout << cur << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

// void allWordsPrefix2() {
//   multimap<string, set<string>> mp;

//   int n;
//   cout << "Enter the number of entries: ";
//   cin >> n;

//   while (n--) {
//     string str;
//     cout << "Enter name: ";
//     cin >> str;

//     string current = "";

//     for (char c : str) {
//       current += c;
//       mp[current].insert(str);
//     }

//     cout << "Enter number of queries: ";
//     cin >> n;

//     while (n--) {
//       string prefix;
//       cout << "Enter prefix: ";
//       cin >> prefix;

//       for (auto it : mp[prefix]) {
//         cout << it << " ";
//       }
//       cout << "\n";
//     }
//     cout << "\n";
//   }
// }

/**
  input => "(()(()))(()(()))"

  ans := 0, define a stack st
  for i in range 0 to size of string S

    if S[i] is opening parentheses
      insert -1 into stack

    otherwise
      if top of stack is -1
        delete from stack and insert 1 into stack

      otherwise
        x := 0
        while top of stack is not -1
          increase x by st, delete from st

        x := x * 2
        delete from st, and insert x

  while stack is not empty
    increase ans by top of st, and delete top element

  return ans.
*/

int scoreOfParentheses(string str) {
  stack<int> st;

  st.push(0);

  for (auto c : str) {
    if (c == '(') {
      st.push(0);
    } else {
      int last = st.top();
      st.pop();

      if (last == 0)
        last = 1;
      else
        last *= 2;

      int parent_par = st.top() + last;
      st.pop();
      st.push(parent_par);
    }
  }

  return st.top();
}

vector<int> asteroidsCollisions(vector<int>& asteroids) {
  vector<int> result;

  for (vector<int>::iterator it = asteroids.begin(); it != asteroids.end(); it++) {
    bool isExploded = false;

    while (!result.empty() && *it < 0 && result.back() > 0) {
      if (result.back() < -(*it)) {
        result.pop_back();
        continue;
      } else if (result.back() == -(*it)) {
        result.pop_back();
      }
      isExploded = true;
      break;
    }

    if (!isExploded) {
      result.push_back(*it);
    }
  }

  return result;
}

vector<int> next_greater_num(vector<int>& v) {
  vector<int> result(v.size(), -1);
  stack<int> pos;

  for (int i = 0; i < (int)v.size(); ++i) {
    while (!pos.empty() && v[i] > v[pos.top()]) {
      result[pos.top()] = v[i];
      pos.pop();
    }
    pos.push(i);
  }
  return result;
}

int main() {
  // vector<int> s1 = {2, 2, 2, 5};
  // vector<int> s2 = {0, 3, 3, 9};
  // vector<int> s3 = {4, 0, 2, 8, 10};

  // cout << max3StacksSum(s1, s2, s3);

  // cout << slidingWindowV2();

  // vector<int> v = {1, 2, 3, 4, 5};

  // vector<int> result = slidingWindowV3(v, 3);

  // for (int item : result) {
  //   cout << item << " ";
  // }

  // queue<int> myQueue;
  // myQueue.push(10);
  // myQueue.push(20);
  // myQueue.push(30);
  // myQueue.push(40);

  // reverseQueue(myQueue);

  // cout << "Queue elements: ";
  // while (!myQueue.empty()) {
  //   cout << myQueue.front() << " ";
  //   myQueue.pop();
  // }
  // cout << "\n";

  // MyStack s;
  // s.push(1);
  // s.push(2);
  // s.push(3);
  // s.push(7);

  // while (!s.empty()) {
  //   cout << s.top() << " ";
  //   s.pop();
  // }

  // cout << reverseNumber(12345);

  // allWordsPrefix2();

  // scoreOfParentheses("(()(()))(()(()))");

  // vector<int> asteroids = {-8, 8, 2};

  // vector<int> res = asteroidsCollisions(asteroids);

  // for (auto ast : res) {
  //   cout << ast << " ";
  // }
  // cout << "\n";

  vector<int> v = {10, 5, 7, 5, 11};
  v = next_greater_num(v);

  return 0;
}