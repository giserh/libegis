#pragma once

#include <vector>
#include <map>
#include "core\Pixel.h"
#include "core\LatLonGrid.h"

namespace libegis {

	class LevelSet
	{
	public:
		LevelSet() {}
		~LevelSet() {}

		/** Creates a level set out of all non missing values in grid. */
		LevelSet(LatLonGrid &input)
		{
			LevelSet levelset;
			for (int i = 0; i < input.getNumLat(); ++i) {
				for (int j = 0; j < input.getNumLon(); ++j) {
					if (input.getValue(i, j) != input.getMissing()) {
						levelset.add(Pixel(i, j, input.getValue(i, j)));
					}
				}
			}
			ls = &levelset; // No original é return levelset...mas não há como retornar nada no construtor
		}

		// Acabei jogado o levelset criado pra cá
		LevelSet *ls = new LevelSet();

		void add(Pixel p)
		{
			std::vector<Pixel> level = data.at(p.getValue());
			if (&level == NULL) {
				std::vector<Pixel> level;
				data.insert(std::make_pair(p.getValue(), level));
			}
			level.push_back(p);
		}

		std::vector<std::map<int, std::vector<Pixel>>> getLevels()
		{
			// return data.entrySet().toArray(new Map.Entry[0]);
		}

	private:
		std::map<int, std::vector<Pixel>> data;
	};
}