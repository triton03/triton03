/*!
 *@brief	�Q�[�����ԃN���X�B
 * �V���O���g���B
 */
#pragma once

#include "tkEngine/timer/tkStopwatch.h"

namespace tkEngine{
	/*!
	 *@brief	�Q�[�����ԁB
	 */
	class CGameTime{
		CGameTime() : 
			m_frameDeltaTime(1.0f/60.0f),
			m_isReady(false)
		{
		}
		~CGameTime()
		{
		}
	public:
		static CGameTime& GetInstance()
		{
			static CGameTime t;
			return t;
		}
		/*!
		 *@brief	1�t���[���̌o�ߎ��Ԃ��擾(�P�ʁE�b)�B
		 */
		float GetFrameDeltaTime() const
		{
			return min(1.0f/10.0f, m_frameDeltaTime);
		}
		void Update()
		{
			if(m_isReady){
				m_sw.Stop();
				m_frameDeltaTime = s_cast<float>( m_sw.GetElapsed() );
			}
			m_sw.Start();
			m_isReady = true;
		}
	private:
		float		m_frameDeltaTime;		//1�t���[���̌o�ߎ��ԁB
		CStopwatch	m_sw;
		bool		m_isReady;
	};
	static CGameTime& GameTime()
	{
		return CGameTime::GetInstance();
	}
}
