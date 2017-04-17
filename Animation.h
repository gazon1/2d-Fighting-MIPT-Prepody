#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "fighter.h"	
#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::IntRect;
using sf::Vector2f;
#include <string>
using std::string;
using std::copy;

class Fighter;

class Animation
	{
		private:

			int * m_frame;
			int m_count;
			int m_size;

		public:

			Animation(const int * frames, int size);
			~Animation();

			IntRect getNextFrame();
			void start();
	};


class Face
	{
		public:

			enum FaceAction
			{
				writhing,
				speaking,
				blinking
			};

			class FacePart
			{
				protected:

					const Face * m_face;

					Texture m_texture;
					Sprite m_sprite;

					Animation m_animation;

					bool m_hidden;

				public:

					friend Face;

					FacePart(const Face * face, const Animation & animation, const char * file);

					void appear();
					void hide();

					virtual void move();
					void draw();
			};

			class ActiveFacePart : public FacePart
			{
				private:

					Animation m_activeAnimation;
					bool m_active;

				public:

					ActiveFacePart(const Face * face, const Animation & activeAnimation, const Animation & animation, const char * file);

					void startAction();
					void stopAction();

					virtual void move();
			};

			struct FaceImageMap
			{ 
				string bases;
				string eyes;
				string eyebrows;
				string mouths;
			};

			struct FaceAnimation
			{
				Animation baseAnime;
				Animation mouthAnime, 	 speakingMouthAnime;
				Animation eyesAnime,  	 blinkingEyesAnime;
				Animation eyebrowsAnime, writhingEyebrowsAnime;
			};

			struct FaceConfig
			{
				FaceImageMap  faceImageMap;
				FaceAnimation faceAnimation;
			};

		private:

			RenderWindow * m_window;
			const Fighter * m_fighter;

			Vector2f m_position;
			double m_angle, m_angularVelocity;
			double m_amplitudeAngle;

			FacePart * m_base;
			ActiveFacePart * m_mouth, * m_eyes, * m_eyebrows;

			int m_action;
			bool m_hidden;

		public:

			friend FacePart;

			Face(const Fighter * fighter, RenderWindow * window, const Vector2f & position, const FaceConfig & cfg);
			~Face();

			void startAction(int action);
			void stopAction(int action);

			void rotate(double angularVelocity, double amplitudeAngle);

			void appear();
			void hide();

			void move();
			void draw();
	};

	class Body
	{
	};
#endif
