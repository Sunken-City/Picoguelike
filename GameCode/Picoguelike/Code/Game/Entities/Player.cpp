#include "Game/Entities/Player.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Renderer/BitmapFont.hpp"
#include "Game/Map/Map.hpp"
#include "Engine/Input/InputSystem.hpp"

Player::Player()
	: Agent()
	, m_action(NO_ACTION)
	, m_direction(EAST)
{
	m_name = "Player";
	m_glyph = '@';
	m_color = RGBA::TURQUOISE;
}

Player::~Player()
{

}

void Player::Update(float deltaSeconds)
{
	Agent::Update(deltaSeconds);
	switch (m_action)
	{
	case NO_ACTION:
		break;
	case MOVE:
		MoveInCurrentDirection();
		m_map->UpdateFOVFrom(m_position, m_viewDistance);
		break;
	default:
		break;
	}
	m_action = NO_ACTION;

	if (InputSystem::instance->WasKeyJustPressed('P'))
	{
		if (!m_path.m_hasBegun)
		{
			Vector2Int goalPosition = m_map->GetRandomCellOfType(Cell::AIR).m_position;
			m_path.InitializePathForStep(m_position, goalPosition);
		}
		m_path.FindPathStep();
	}
}

void Player::Render() const
{
	Agent::Render();
	Vector2 mapOffset(0.0f, 0.0f);
	const char* characterString = &m_glyph;
	Renderer::instance->DrawText2D((Vector2(m_position) * 25.0f) + mapOffset, characterString, 1.0f, m_color, false, BitmapFont::CreateOrGetFontFromGlyphSheet("Runescape"));
}

void Player::MoveInCurrentDirection()
{
	switch (m_direction)
	{
	case EAST:
		AttemptStep(Vector2Int::UNIT_X);
		break;
	case NORTH_EAST:
		AttemptStep(Vector2Int::ONE);
		break;
	case NORTH:
		AttemptStep(Vector2Int::UNIT_Y);
		break;
	case NORTH_WEST:
		AttemptStep(Vector2Int(-1, 1));
		break;
	case WEST:
		AttemptStep(-Vector2Int::UNIT_X);
		break;
	case SOUTH_WEST:
		AttemptStep(-Vector2Int::ONE);
		break;
	case SOUTH:
		AttemptStep(-Vector2Int::UNIT_Y);
		break;
	case SOUTH_EAST:
		AttemptStep(Vector2Int(1, -1));
		break;
	case NUM_DIRECTIONS:
		ERROR_AND_DIE("Invalid Direction Attempted");
		break;
	default:
		break;
	}
}

void Player::QueueMove(Direction dir)
{
	m_direction = dir;
	m_action = Action::MOVE;
}
