#pragma once

#include <string>
#include <utility>
#include <vector>

namespace Graph
{
    class Visualizer
    {
        public:
            void AddGraph(const std::string& json);
            void AddGraph(const std::string& title, const std::string& json);
            void Visualize(const std::string& path) const;

        private:
            std::vector<std::pair<std::string, std::string>> v_graphs;
    };
}
