#include "polygon.hpp"
#include <ostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "predicates.hpp"

std::istream& novikov::operator>>(std::istream& in, Polygon& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::size_t n{};
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > points;
  points.reserve(n);
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, n, std::back_inserter(points));
  if (in && points.size() == n)
  {
    rhs.points = std::move(points);
  }

  return in;
}

std::ostream& novikov::operator<<(std::ostream& out, const Polygon& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << rhs.points.size() << " ";
  std::copy(rhs.points.cbegin(), rhs.points.cend(), std::ostream_iterator< Point >{ out, " " });
  return out;
}

bool novikov::operator==(const Polygon& lhs, const Polygon& rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  return std::equal(lhs.points.cbegin(), lhs.points.cend(), rhs.points.cbegin());
}

double novikov::getArea(const Polygon& rhs)
{
  using namespace std::placeholders;
  auto acc_area = std::bind(AccumulateArea{ rhs.points[1] }, _1, _2, rhs.points[0]);
  return std::accumulate(rhs.points.cbegin(), rhs.points.cend(), 0.0, acc_area);
}

int novikov::minX(const Polygon& rhs)
{
  return std::min_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsX)->x;
}

int novikov::minY(const Polygon& rhs)
{
  return std::min_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY)->y;
}

int novikov::maxX(const Polygon& rhs)
{
  return std::max_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsX)->x;
}

int novikov::maxY(const Polygon& rhs)
{
  return std::max_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY)->y;
}