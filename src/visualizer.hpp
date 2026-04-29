#pragma once

#include <string>
#include <vector>

namespace Graph
{
    class Visualizer
    {
        public:
            void AddGraph(const std::string& json);
            void Visualize(const std::string& path) const;

        private:
            std::vector<std::string> v_graphs;
    };
}
