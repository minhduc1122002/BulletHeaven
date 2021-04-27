#include "Game_Utils.h"
#include "Enemy.h"

using namespace std;

bool Game_Utils::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    if(object1.x+object1.w>=object2.x && object2.x+object2.w>=object1.x
       && object1.y+object1.h>=object2.y && object2.y+object2.h>=object1.y)
    {
        return true;
    }
    return false;
}
std::string Game_Utils::number_to_string(int number)
{
    stringstream ss;
    ss << setw(6) << setfill('0') << number;
    string val_score;
    ss >> val_score;
    return val_score;
}
string Game_Utils::GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path.c_str(),ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void Game_Utils::UpdateHighScore(string path,const int& score, string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path.c_str(), ios::out);

	ConvertToInt >> oldHighScore;
	if (score>oldHighScore)
	{
		oldHighScore=score;
	}
	newHighScore=Game_Utils::number_to_string(oldHighScore);
	old_high_score=newHighScore;
	HighScoreFile << newHighScore;
}

