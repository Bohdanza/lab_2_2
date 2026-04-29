#pragma once

#include <string>
#include <vector>

namespace graph
{
    class Visualizer
    {
        public:
            void AddGraph(const std::string& json);
            void Visualize(const std::string& path) const;

        private:
            std::vector<std::string> graphs_;
    };
}
