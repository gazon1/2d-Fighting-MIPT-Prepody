#include "Animation.h"

Face::Face(const Fighter * fighter, RenderWindow * window, const Vector2f & position, const FaceConfig & cfg)
		:	m_window(window),
			m_fighter(fighter),
			m_position(position),
			m_angle(0), m_angularVelocity(0),
			m_amplitudeAngle(0),
			m_action(blinking),
			m_hidden(false)
{
		m_base  = new FacePart          (this, cfg.faceAnimation.baseAnime,			    								 cfg.faceImageMap.bases.c_str());
		m_mouth = new ActiveFacePart    (this, cfg.faceAnimation.speakingMouthAnime,    cfg.faceAnimation.mouthAnime, 	 cfg.faceImageMap.eyes.c_str());
		m_eyes  = new ActiveFacePart    (this, cfg.faceAnimation.blinkingEyesAnime,		cfg.faceAnimation.eyesAnime, 	 cfg.faceImageMap.eyes.c_str());
		m_eyebrows = new ActiveFacePart (this, cfg.faceAnimation.writhingEyebrowsAnime,	cfg.faceAnimation.eyebrowsAnime, cfg.faceImageMap.eyebrows.c_str());
};

Face::~Face()
{
		delete m_base;
		delete m_eyes;
		delete m_mouth;
		delete m_eyebrows;
};

void Face::rotate(double angularVelocity, double amplitudeAngle)
{
		m_angularVelocity = angularVelocity;
		m_amplitudeAngle = amplitudeAngle;
};

void Face::startAction(int action)
{
		switch(action)
		{
				case speaking: m_mouth->startAction();
				case writhing: m_eyebrows->startAction();
				case blinking: m_eyes->startAction();
		}
};

void Face::move()
{
		m_eyes->move();
		m_mouth->move();
		m_eyebrows->move();
};

void Face::draw()
{
		m_eyes->draw();
		m_mouth->draw();
		m_eyebrows->draw();
};

Face::FacePart::FacePart(const Face * face, const Animation & animation, const char * file)
	: m_face(face),
	  m_animation(animation),
	  m_hidden(false)
{
		m_texture.loadFromFile(file); m_sprite.setTexture(m_texture); 
		m_sprite.setTextureRect(m_animation.getNextFrame()); 
		m_sprite.setPosition(face->m_position.X(), 
		face->m_position.Y());
};

void Face::FacePart::appear()
{
		m_hidden = false;
};

void Face::FacePart::hide()
{
		m_hidden = true;
};

void Face::FacePart::move()
{
		m_sprite.setTextureRect(m_animation.getNextFrame());
		//m_sprite.setPosition(m_position.X(), m_position.Y());
};

void Face::FacePart::draw()
{
		m_face->m_window->draw(m_sprite);
};


Face::ActiveFacePart::ActiveFacePart(const Face * face, const Animation & activeAnimation, const Animation & animation, const char * file)
: m_activeAnimation(activeAnimation),
  FacePart(face, animation, file)
{};

void Face::ActiveFacePart::startAction()
{
		m_active = true;
		m_activeAnimation.start();
};

void Face::ActiveFacePart::stopAction()
{
		m_active = false;
};


void Face::ActiveFacePart::move()
{
switch(m_active)
{
	case true:  m_sprite.setTextureRect(m_activeAnimation.getNextFrame());  break;
	case false: m_sprite.setTextureRect(m_animation.getNextFrame());		break;
}

//m_sprite.setPosition(m_position.X(), m_position.Y());
};

Animation::Animation(const int * frames, int size)
: m_frame(new int[size]),
  m_size(size),
  m_count(0)
{
	copy(frames, frames + size, m_frame);
};

Animation::~Animation()
{
delete [] m_frame;
};

IntRect Animation::getNextFrame()
{
auto Frame = IntRect(300 * m_frame[m_count], 0, 300, 300);

if(m_count++ > m_size)
	m_count = 0;

return Frame;
};

void Animation::start()
{
m_count = 0;
};
