#include <iostream>
#include <vector>

// kilkanaście wierszy kodu zalane kawą


std::ostream& operator<<(std::ostream & F, std::vector<int> const& v)
{
  const int N = 10;
  const int ile = std::min<int>(N, v.size());

  F << "[";
  for (int i = 0; i < ile - 1; i++)
    F << v[i] << ", ";
  F << v[ile-1];
  if (v.size() > N)
    F << ",...]";
  else
    F << "]";

  return F;
}

void test(std::ostream & F, std::vector<int> const& v)
{
  std::cout << "v = " << v << "\n"; 
  int suma = sum(v);
  std::cout << "sum(v) = " << suma << "\n";
  std::vector<int> w (v);
  reverse(w);
  std::cout << "reversed v = " << w << "\n"; 
  w.resize(13);
  std::cout << "resized v = " << w << "\n"; 
}

int main()
{
  std::vector<int> v {3, 4, -6, 8, 5};
  test(std::cout, v);

  std::cout << "\n*** performing iota ***\n";
  iota(v); 
  test(std::cout, v);

  std::cout << "good bye!\n";
}
