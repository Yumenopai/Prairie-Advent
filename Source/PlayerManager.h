#pragma once

#include <vector>
#include <set>
#include "Player.h"
#include "Player1P.h"
#include "PlayerAI.h"

class PlayerManager
{
private:
	PlayerManager() {}
	~PlayerManager() {}

public:
	//唯一のインスタンス取得
	static PlayerManager& Instance()
	{
		static PlayerManager instance;
		return instance;
	}

	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void ShadowRender(const RenderContext& rc, ShadowMap* shadowMap);
	void Render(const RenderContext& rc, ModelShader* shader);

	//デバッグプリミティブ描画
	void Render2d(const RenderContext & rc, Sprite* gauge);

	//エネミー登録
	void Register(Player* player);

	//エネミー数取得
	int GetPlayerCount() const { return static_cast<int>(players.size()); }

	//エネミー取得
	Player* GetPlayer(int index) { return players.at(index); }

	//エネミー削除
	void Remove(Player* player);

	//エネミー全削除
	void Clear();
	void CollisionPlayerVsPlayer();

	//複数管理でポインターをここで管理
	std::vector<Player*> players;

private:

	std::set<Player*> removes;
};