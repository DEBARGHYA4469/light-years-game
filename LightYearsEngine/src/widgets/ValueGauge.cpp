#include <widgets/ValueGauge.h>
#include <framework/AssetManager.h>

// Initializer's list order depend on the variable order in the header  

ly::ValueGauge::ValueGauge(const sf::Vector2f& size, float initialPercent, const sf::Color& FontBarColor, const sf::Color& BackBarColor):
	mTextFont{ ly::AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future_thin.ttf") },
	mText("Hello", *mTextFont),
	mPercent (initialPercent),
	mBarFront { size },
	mBarBackground { size },
	mBarBackgroundColor { BackBarColor }, 
	mBarForegroundColor { FontBarColor }
{
	mBarBackground.setFillColor(mBarBackgroundColor);
	mBarFront.setFillColor(mBarForegroundColor);
	SetTextSize(40);
}

ly::ValueGauge::~ValueGauge() {
	LOG("ValueGauge::Destructor Called");
}

bool ly::ValueGauge::HandleEvent(const sf::Event& event)
{
	return false;
}

void ly::ValueGauge::UpdateValue(float value, float maxValue)
{	

	if (maxValue) mPercent = value / maxValue;
	std::string str = std::to_string((int) (mPercent * 100)) + " %";
	mText.setString(str);
	sf::Vector2f barSize = mBarBackground.getSize();
	mBarFront.setSize({ barSize.x * mPercent, barSize.y });
	CenterText();
}

void ly::ValueGauge::CenterText() {
	sf::Vector2f widgetCenter = GetCenterPosition();
	sf::FloatRect textBound = mText.getGlobalBounds();
	mText.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2.f , textBound.height});
}

void ly::ValueGauge::Draw(sf::RenderWindow& windowRef)
{
	windowRef.draw(mBarBackground);
	windowRef.draw(mBarFront);
	windowRef.draw(mText);
}

void ly::ValueGauge::LocationUpdated(const sf::Vector2f& newLocation)
{
	//mText.setPosition(newLocation + sf::Vector2f{mBarBackground.getSize().x / 3.f, -15});
	mBarBackground.setPosition (newLocation);
	mBarFront.setPosition (newLocation);
	CenterText();
}

void ly::ValueGauge::RotationUpdated(float newRotation)
{
	mText.setRotation(newRotation);
	mBarBackground.setRotation(newRotation);
	mBarFront.setRotation(newRotation);
}
