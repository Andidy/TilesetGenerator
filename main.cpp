#include <SFML/Graphics.hpp>

// 0 blank, 1 dot, 2 edge, 3 corner, 4 r_edge
int tile[192] = {
  0, 0, 3, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 3,
  0, 0, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 0, 1, 4, 3,
  3, 4, 4, 4, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 4, 3,
  2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 2,
  2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2,
  2, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 2, 3, 3,
  2, 0, 0, 1, 1, 2, 2, 0, 0, 1, 1, 1, 1, 2, 3, 3,
  2, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2,
  2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 2,
  2, 1, 4, 4, 1, 0, 0, 1, 1, 0, 0, 0, 0, 2, 2, 2,
  2, 1, 4, 4, 1, 0, 0, 2, 2, 0, 0, 0, 0, 1, 1, 2,
  3, 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 3
};

// 0 normal, 1 horz, 2 vert, 3 horz vert
int pose[192] = {
  0, 0, 3, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2,
  0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  3, 2, 2, 2, 3, 0, 0, 2, 3, 0, 0, 0, 0, 2, 2, 2,
  1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  1, 2, 3, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0,
  1, 0, 0, 2, 3, 0, 1, 0, 0, 2, 3, 2, 3, 0, 3, 2,
  1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  1, 2, 3, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0,
  1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
  1, 2, 2, 2, 3, 0, 0, 0, 1, 0, 0, 0, 0, 2, 3, 0,
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
};

int index(int x, int y) {
	return x + y * 16;
}

int main() {
	for (int i = 0; i < 4; i++) {
		sf::Image output;
		output.create(128, 96, sf::Color::Black);

		sf::Image input;

		char str[128];
		sprintf_s(str, 128, "test_%d.png", i);
		if (!input.loadFromFile(str)) {
			printf("failed to find input image\n");
			//return -1;
		}

		sf::Image blank;
		blank.create(8, 8);
		blank.copy(input, 0, 0, sf::IntRect(0, 0, 8, 8));

		sf::Image dot;
		dot.create(8, 8);
		dot.copy(input, 0, 0, sf::IntRect(8, 0, 8, 8));

		sf::Image edge;
		edge.create(8, 8);
		edge.copy(input, 0, 0, sf::IntRect(16, 0, 8, 8));

		sf::Image corner;
		corner.create(8, 8);
		corner.copy(input, 0, 0, sf::IntRect(24, 0, 8, 8));

		sf::Image r_edge;
		r_edge.create(8, 8);

		for (int i = 0; i < edge.getSize().x; i++) {
			for (int j = 0; j < edge.getSize().y; j++) {
				r_edge.setPixel(edge.getSize().y - 1 - j, i, edge.getPixel(i, j));
			}
		}


		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 16; x++) {
				sf::Image temp;
				temp.create(8, 8);

				switch (tile[index(x, y)]) {
					case 0:
						switch (pose[index(x, y)]) {
							case 0:
							case 1:
							case 2:
							case 3:
								output.copy(blank, 8 * x, 8 * y);
								break;
						}
						break;
					case 1:
						temp.copy(dot, 0, 0);
						switch (pose[index(x, y)]) {
							case 0:
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 1:
								temp.flipHorizontally();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 2:
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 3:
								temp.flipHorizontally();
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
						}
						break;
					case 2:
						temp.copy(edge, 0, 0);
						switch (pose[index(x, y)]) {
							case 0:
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 1:
								temp.flipHorizontally();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 2:
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 3:
								temp.flipHorizontally();
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
						}
						break;
					case 3:
						temp.copy(corner, 0, 0);
						switch (pose[index(x, y)]) {
							case 0:
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 1:
								temp.flipHorizontally();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 2:
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 3:
								temp.flipHorizontally();
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
						}
						break;
					case 4:
						temp.copy(r_edge, 0, 0);
						switch (pose[index(x, y)]) {
							case 0:
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 1:
								temp.flipHorizontally();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 2:
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
							case 3:
								temp.flipHorizontally();
								temp.flipVertically();
								output.copy(temp, 8 * x, 8 * y);
								break;
						}
						break;
				}
			}
		}

		sprintf_s(str, 128, "output_%d.png", i);
		output.saveToFile(str);
	}

	return 0;
}