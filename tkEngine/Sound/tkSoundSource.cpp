/*!
 * @brief	�����N���X�B
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/Sound/tkSoundSource.h"


namespace tkEngine{
	CSoundSource::CSoundSource()
	{
	}
	CSoundSource::~CSoundSource()
	{
		Release();
	}
	void CSoundSource::Init( char* filePath )
	{
		m_waveFile.Open(filePath);
		m_buffer.reset(new char[m_waveFile.GetSize()]);
		unsigned int dummy;
		m_waveFile.Read(m_buffer.get(), m_waveFile.GetSize(), &dummy);
		//�T�E���h�{�C�X�\�[�X���쐬�B
		m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(&m_waveFile);
	}
	void CSoundSource::InitStreaming(char* filePath, unsigned int ringBufferSize, unsigned int bufferSize)
	{
		m_waveFile.Open(filePath);
		m_isStreaming = true;
		m_streamingBufferSize = bufferSize;
		m_buffer.reset( new char[ringBufferSize]);
		m_ringBufferSize = ringBufferSize;
		m_readStartPos = 0;
		m_currentBufferingSize = 0;
		//�T�E���h�{�C�X�\�[�X���쐬�B
		m_sourceVoice = SoundEngine().CreateXAudio2SourceVoice(&m_waveFile);
		m_sourceVoice->Start(0,0);
	}
	void CSoundSource::Release()
	{
		m_waveFile.Release();
		if (m_sourceVoice != nullptr) {
			m_sourceVoice->DestroyVoice();
			m_sourceVoice = nullptr;
		}
		DeleteGO(this);
	}
	void CSoundSource::Play(char* buff, unsigned int bufferSize)
	{
		XAUDIO2_BUFFER buffer = { 0 };
		buffer.pAudioData = (BYTE*)buff;
		buffer.Flags = XAUDIO2_END_OF_STREAM;  // tell the source voice not to expect any data after this buffer
		buffer.AudioBytes = bufferSize;
		if (m_sourceVoice != nullptr && bufferSize > 0) {
			//�Đ��J�n�B
			if (FAILED(m_sourceVoice->SubmitSourceBuffer(&buffer))) {
				Release();
				TK_LOG("Failed m_sourceVoice->SubmitSourceBuffer");
				return;
			}

		}
	}
	
	void CSoundSource::StartStreamingBuffring()
	{
		char* readStartBuff = m_buffer.get();
		m_readStartPos += m_currentBufferingSize;
		if (m_readStartPos + m_streamingBufferSize >= m_ringBufferSize) {
			//�����O�o�b�t�@�̃T�C�Y�𒴂���B
			//�z����B
			m_readStartPos = 0;
		}
		m_waveFile.ReadAsync(&readStartBuff[m_readStartPos], m_streamingBufferSize, &m_currentBufferingSize);
		m_streamingState = enStreamingBuffering;
	}
	void CSoundSource::Play(bool isLoop)
	{
		if (m_isPlaying) {
			//�Đ����̂��̂��ĊJ����B
			m_sourceVoice->Start(0);
		}
		else {
			if (m_isStreaming) {
				//�o�b�t�@�����O�J�n
				StartStreamingBuffring();
			}
			else {
				m_sourceVoice->FlushSourceBuffers();
				m_sourceVoice->Start(0);
				Play(m_buffer.get(), m_waveFile.GetSize());
			}
			m_isPlaying = true;
		}
		m_isLoop = isLoop;
	}
	void CSoundSource::UpdateStreaming()
	{
		if (!m_isPlaying) {
			return;
		}
		if (m_streamingState == enStreamingBuffering) {
			//�o�b�t�@�����O���B
			if (m_waveFile.IsReadEnd()) {
				//�o�b�t�@�����O���I������B
				m_streamingState = enStreamingQueueing;
			}
		}
		if (m_streamingState == enStreamingQueueing) {
			//�L���[�C���O���B
			XAUDIO2_VOICE_STATE state;
			m_sourceVoice->GetState(&state);
			if (state.BuffersQueued <= 2) {	//�L���[�C���O����Ă���o�b�t�@���Q�ȉ��ɂȂ�����L���[�C���O�ł���B
				Play(&m_buffer[m_readStartPos], m_currentBufferingSize);
				if (m_currentBufferingSize == 0) {
					//�ǂݍ��񂾃T�C�Y���O�Ƃ������Ƃ͖��[�܂œǂݍ��݂��I������Ƃ������ƁB
					if (m_isLoop) {
						//���[�v����H
						//wave�t�@�C���̓ǂݍ��݈ʒu�����Z�b�g���ăo�b�t�@�����O�ĊJ�B
						m_waveFile.ResetFile();
						StartStreamingBuffring();
					}
					else {
						//���[�v���Ȃ��ꍇ�̓L���[����ɂȂ�����Đ��I���B
						if (state.BuffersQueued == 0) {
							//�Đ��I���B
							m_isPlaying = false;
							DeleteGO(this);
						}
					}
				}
				else {
					//�����o�b�t�@�����O����B
					StartStreamingBuffring();
				}
			}
		}
	}
	void CSoundSource::UpdateOnMemory()
	{
		if (!m_isPlaying) {
			return;
		}
		XAUDIO2_VOICE_STATE state;
		m_sourceVoice->GetState(&state);
		if (state.BuffersQueued <= 0) {
			m_isPlaying = false;
			if (m_isLoop) {
				//���[�v�B
				Play(m_isLoop);
			}
			else {
				DeleteGO(this);
			}
		}
	}
	void CSoundSource::Update()
	{
		if (m_isStreaming) {
			//�X�g���[�~���O�Đ����̍X�V�B
			UpdateStreaming();
		}
		else {
			//�I���������Đ����̍X�V�����B
			UpdateOnMemory();
		}
	}
}
