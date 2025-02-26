#include "JW01AudioProcessorEditor.h"

// 親クラスのコンストラクタを呼び出し、プロセッサへの参照を保持
JW01AudioProcessorEditor::JW01AudioProcessorEditor(JW01AudioProcessor& p): AudioProcessorEditor(&p), processor(p) {
    // オーバードライブラベルの追加
    overdriveLabel.setText("Overdrive", juce::dontSendNotification);
    addAndMakeVisible(overdriveLabel);
    
    // ゲインラベルの追加
    gainLabel.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(gainLabel);

    // オーバードライブスライダーのスタイルを設定しエディタに追加&AudioProcessorValueTreeStateに接続しパラメータと連動
    overdriveSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    overdriveSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(overdriveSlider);
    NotificationName overdrive = NotificationName::Overdrive;
    std::string overdriveString = std::string(toString(overdrive));
    overdriveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, overdriveString, overdriveSlider);
    
    // ゲインスライダーのスタイルを設定しエディタに追加&AudioProcessorValueTreeStateに接続しパラメータと連動
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    addAndMakeVisible(gainSlider);
    NotificationName gain = NotificationName::Gain;
    std::string gainString = std::string(toString(gain));
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, gainString, gainSlider);

    // エディタのウィンドウサイズを設定
    setSize(750, 500);
}

// デストラクタ（特にリソースの解放処理は不要）
JW01AudioProcessorEditor::~JW01AudioProcessorEditor() {}

// エディタの描画処理
void JW01AudioProcessorEditor::paint(juce::Graphics& g) {
    // 背景を黒に塗りつぶす
    g.fillAll(juce::Colours::black);
    // テキストの色を白に設定
    g.setColour(juce::Colours::white);
    // フォントサイズを 15.0f に設定
    g.setFont(15.0f);
    // プラグイン名を上部中央に描画
    g.drawFittedText("JW01 Plugin", getLocalBounds(), juce::Justification::centredTop, 1);
}

// コンポーネントのリサイズ時にスライダーの位置を調整
void JW01AudioProcessorEditor::resized() {
    overdriveLabel.setBounds(20, 20, getWidth() - 40, 20);
    overdriveSlider.setBounds(20, 40, getWidth() - 40, 20);
    gainLabel.setBounds(20, 60, getWidth() - 40, 20);
    gainSlider.setBounds(20, 80, getWidth() - 40, 20);
}
