#pragma once
#include <vector>
#include <random>

namespace vec
{
	namespace mathlib
	{
		sp_nativeinfo_t g_vMathLibNatives[];
		bool SDK_OnLoad(char* error, size_t maxlen, bool late);

		namespace API
		{
			static cell_t GetAliasMethodValue(IPluginContext*, const cell_t*);
			static cell_t GetPresudoExponentialDistributionValue(IPluginContext*, const cell_t*);
			static cell_t GetPresudoExponentialDistributionValue2(IPluginContext*, const cell_t*);
		}

		template<typename T = float>
		class AliasMethod
		{
		public:
			AliasMethod(std::vector<T> passIn) : m_ProbTable(passIn) { Generate(); }
			std::size_t Get()
			{
				std::size_t value = std::uniform_int_distribution<std::size_t>(0, TableSize() - 1)(rd);
				bool toss = std::uniform_real_distribution<float>(0, 1)(rd) < m_ProbTable[value];
				return toss ? value : m_Alias[value];
			}
		private:
			void Generate()
			{
				if (!TableSize()) return;

				m_Alias = new std::size_t[TableSize()];
				m_Accept = new double[TableSize()];

				double average = 1.0 / TableSize();

				for (auto& i : m_ProbTable) i *= TableSize();

				std::list<std::size_t> m_Small;
				std::list<std::size_t> m_Large;

				for (std::size_t i = 0; i < TableSize(); i++) (m_ProbTable[i] < 1.f) ? m_Small.push_back(i) : m_Large.push_back(i);

				while (!m_Small.empty() && !m_Large.empty())
				{
					std::size_t small_idx = m_Small.back();
					m_Small.pop_back();
					std::size_t large_idx = m_Large.back();
					m_Large.pop_back();

					m_Accept[small_idx] = m_ProbTable[small_idx];
					m_Alias[small_idx] = large_idx;
					m_ProbTable[large_idx] -= 1 - m_ProbTable[small_idx];

					(m_ProbTable[large_idx] < 1.f) ? m_Small.push_back(large_idx) : m_Large.push_back(large_idx);
				}

				while (!m_Small.empty())
				{
					m_Accept[m_Small.back()] = 1.f;
					m_Small.pop_back();
				}
				while (!m_Large.empty())
				{
					m_Accept[m_Large.back()] = 1.f;
					m_Large.pop_back();
				}
			}

			std::size_t TableSize() { return m_ProbTable.size(); }

			std::random_device rd;
			std::vector<T> m_ProbTable;

			std::size_t* m_Alias;
			double* m_Accept;
		};
		inline std::size_t GetPresudoExponentialDistributionValue(int rate)
		{
			std::random_device rd;
			
			std::uniform_real_distribution<> dist(0, 1);
			while (true)
			{
				std::size_t p = std::floor(std::log(1 - dist(rd)) * (-rate));
				if (int(p) < rate)
				{
					return p;
					break;
				}
			}
		}

		inline std::size_t GetPresudoExponentialDistributionValue2(int rate, std::size_t maxIterCnt)
		{
			std::random_device rd;
			std::uniform_real_distribution<> dist(0, 1);
			std::size_t i = 0;
			while (i <= maxIterCnt)
			{
				std::size_t p = std::floor(std::log(1 - dist(rd)) * (-rate));
				if (int(p) < rate)
				{
					return p;
					break;
				}
				i++;
			}
			return rate - 1;
		}
	}
}