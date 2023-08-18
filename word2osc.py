import struct
import pyaudio
import pvporcupine

from pythonosc import udp_client

porcupine = pvporcupine.create(
    access_key="K9OGDVwxSaXvx8oX56OnDALO9CacwfdV/caLJirKU6gjG+JOt2l9Pg==",
    keyword_paths=['src/パスタ_ja_mac_v2_2_0.ppn', 'src/ラーメン_ja_mac_v2_2_0.ppn'], 
    model_path='src/porcupine_params_ja.pv'
)

def word2osc(audio_stream):
    pcm = audio_stream.read(porcupine.frame_length)
    pcm = struct.unpack_from("h" * porcupine.frame_length, pcm)
    result = porcupine.process(pcm)

    if result == 0:
        print("パスタ Wake Word!")
        wakeword = "パスタ"
        
        client.send_message("/wakeword", wakeword)
        client.send_message("/num", 0)

        audio_stream.stop_stream()
        audio_stream.close()
            
    elif result == 1:
        print("ラーメン Wake Word!")
        wakeword = "ラーメン"
        client.send_message("/wakeword", wakeword)
        client.send_message("/num", 1)

        audio_stream.stop_stream()
        audio_stream.close()

if __name__ == '__main__':
    pa = pyaudio.PyAudio()
    audio_stream = pa.open(
        rate=porcupine.sample_rate,
        channels=1,
        format=pyaudio.paInt16,
        input=True,
        frames_per_buffer=porcupine.frame_length)

    client = udp_client.SimpleUDPClient("127.0.0.1", 3296)

    while True:
        word2osc(audio_stream)
        audio_stream = pa.open(
            rate=porcupine.sample_rate,
            channels=1,
            format=pyaudio.paInt16,
            input=True,
            frames_per_buffer=porcupine.frame_length)
            