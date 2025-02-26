#include "JW01AudioProcessor.h"
#include "JW01AudioProcessorEditor.h"
#include <cmath>

// プラグインのインスタンスを作成する関数(JUCEによって呼び出される)
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new JW01AudioProcessor();
}

// コンストラクタ(プラグインの初期化処理)
JW01AudioProcessor::JW01AudioProcessor()
: AudioProcessor (BusesProperties()
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
, parameters(*this, nullptr, "PARAMETERS", {
    // "overdrive"パラメータを作成(パラメータID・表示名・最小値・最大値・デフォルト値)
    std::make_unique<juce::AudioParameterFloat>("Overdrive", "Overdrive", 1.0f, 10.0f, 1.0f)
})
{
    // "overdrive"パラメータの値を取得(リアルタイム処理用)
    overdriveParam = parameters.getRawParameterValue("Overdrive");
}

// デストラクタ(特にリソースの解放処理は不要)
JW01AudioProcessor::~JW01AudioProcessor() {}

// オーディオ処理の準備(サンプルレートやバッファサイズが渡される)
void JW01AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}

// リソース解放(特に何もしていないが、必要ならここに追加)
void JW01AudioProcessor::releaseResources() {}

// 実際に音を処理するロジック(ゲイン調整・エフェクトの適用・フィルタリング等)を記述
void JW01AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    // 現在のゲインパラメータの値を取得
    float overdriveValue = overdriveParam->load();
    // 各チャンネル(L/R)に対して処理を実行
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        
        //　TONEの処理をここに入れる

        // オーバードライブの処理
        float* channelData = buffer.getWritePointer(channel);
        // 各サンプルにオーバードライブを適用
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            // 【ソフトクリッピング(オーバードライブ効果)】
            channelData[sample] = std::tanh(overdriveValue * channelData[sample]);
            // 【ハードクリッピング(より強い歪み)】
            // channelData[sample] = juce::jlimit(-overdriveValue, overdriveValue, channelData[sample]);
            // 【Exponential Drive(より自然な歪み)】
            // channelData[sample] = std::copysign(1.0f - std::exp(-std::abs(drive * channelData[sample])), channelData[sample]);
        }
        
        //        // アウトプットゲインの処理
        //        // チャンネルのバッファデータを取得(実際にはこの行は不要)
        //        buffer.getWritePointer(channel);
        //        // バッファのサンプルにゲインを適用
        //        buffer.applyGain(channel, 0, buffer.getNumSamples(), gainValue);

    }
}

//==============================================================================
// プラグイン情報

// プラグインの名前を返す関数
const juce::String JW01AudioProcessor::getName() const {
    return "JW01 Plugin";
}

// MIDI信号を受け入れるかどうか。を返す関数。このプラグインではMIDIを受け付けない
bool JW01AudioProcessor::acceptsMidi() const {
    return false;
}

// MIDI信号を出力するかどうか。このプラグインはMIDIを出力しない
bool JW01AudioProcessor::producesMidi() const {
    return false;
}

// プラグインの尾音(音が消えるまでの時間)を秒単位で返す関数。このプラグインに尾音はない
double JW01AudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

// プログラム数を返す関数。プラグインに設定されたプログラム数は1
int JW01AudioProcessor::getNumPrograms() {
    return 1;
}

// 現在選ばれているプログラムのインデックスを返す関数。現在のプログラムは常に0番目
int JW01AudioProcessor::getCurrentProgram() {
    return 0;
}

// 現在のプログラムを変更する関数。ここでは特に処理を行わない
void JW01AudioProcessor::setCurrentProgram(int index) {}

// 特定のプログラムの名前を返す関数。インデックスが指定されるがこの実装では名前は返さない(空文字列を返す)
const juce::String JW01AudioProcessor::getProgramName(int index) {
    return {};
}

// プログラム名を変更する関数。この実装では変更処理を行わない。
void JW01AudioProcessor::changeProgramName(int index, const juce::String& newName) {}

//==============================================================================
// ステート情報

// プラグインの現在の状態を保存する関数。パラメーターの状態をコピーしXML形式に変換してバイナリデータとしてdestDataに保存
void JW01AudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // パラメーターの状態をXMLに変換
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    // XMLデータをバイナリに変換してdestDataにコピー
    copyXmlToBinary(*xml, destData);
}

// プラグインの状態を復元する関数。保存されているバイナリデータをXMLに変換しそれを使用してパラメーターの状態を復元
void JW01AudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // バイナリデータからXML形式で状態を取得
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    // XMLが有効な場合、パラメーターの状態を復元
    if (xmlState != nullptr) {
        // 既存のパラメーター状態を置き換え
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

//==============================================================================
// エディター(UI)を作成

// エディターがあるかどうかを返す関数。trueに設定しているのでプラグインにはエディターが常に存在
bool JW01AudioProcessor::hasEditor() const {
    return true;
}

// AudioProcessorEditorのインスタンスを作成する関数。プラグインのエディター(ユーザーインターフェース)を返却
// JW01AudioProcessorEditorクラスはカスタムのエディタークラスでAudioProcessorのUIを表示する。
juce::AudioProcessorEditor* JW01AudioProcessor::createEditor() {
    // エディターを作成して返す
    return new JW01AudioProcessorEditor(*this);
}
