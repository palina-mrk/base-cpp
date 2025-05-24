#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <cmath>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()}, N{0} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
    ++N;
	}

	double eval() const override {
		return N ? m_min : 0;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
  int N;
};

class Max : public IStatistics {
public:
  Max() : m_max{std::numeric_limits<double>::min()}, N{0} {
  }

  void update(double next) override {
    if (next > m_max) {
      m_max = next;
    }
    ++N;
  }

  double eval() const override {
    return N ? m_max : 0;
  }

  const char * name() const override {
    return "max";
  }

private:
  // m_max = DOUBLE_MAX
  double m_max;
  size_t N;
};

class Mean : public IStatistics {
public:
  Mean() : m_sum{0}, N{0} {
  }

  void update(double next) override {
    m_sum += next;
    ++N;
  }

  double eval() const override {
    return (N ? m_sum / (double) N : 0 );
  }

  const char * name() const override {
    return "mean";
  }

private:
  double m_sum;    // сумма
  size_t N;        // длина массива
};

class StandardDeviation : public IStatistics {
public:
  StandardDeviation() : m_sum_sqr{0}, m_sum{0}, N{0} {
  }

  void update(double next) override {
    m_sum += next;
    m_sum_sqr += (next * next);
    ++N;
  }

  double eval() const override {
    if(!N)
      return 0;
    double squared_result, m_mean;
    m_mean = m_sum / (double) N;
    squared_result = m_sum_sqr/(double) N - m_mean*m_mean;
    return std::sqrt(squared_result);
  }

  const char * name() const override {
    return "sqt";
  }

private:
  double m_sum_sqr; // сумма квадратов
  double m_sum;    // сумма
  size_t N;        // длина массива
};


int main() {
    std::vector<std::unique_ptr<IStatistics>> stats;
    stats.emplace_back(dynamic_cast<IStatistics*>(new Min));
    stats.emplace_back(dynamic_cast<IStatistics*>(new Max));
    stats.emplace_back(dynamic_cast<IStatistics*>(new Mean));
    stats.emplace_back(dynamic_cast<IStatistics*>(new StandardDeviation));

    double val;
    while (std::cin >> val) {
        for (auto& stat: stats) {
            stat->update(val);
        }
    }
    for (auto& stat: stats) {
        std::cout << stat->name() << ":\t" << stat->eval() << std::endl;
    }
}
