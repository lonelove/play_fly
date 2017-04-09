#include "RnakLayer.h"
#include"MainScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
// ������ص�ͷ�ļ�
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
// ʹ����������ռ�
USING_NS_UM_SOCIAL;
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
/*
* ����ص�
* @param platform Ҫ������Ŀ��ƽ̨
* @param stCode ������, 200�������ɹ�, 100����ʼ����
* @param errorMsg ����ʧ��ʱ�Ĵ�����Ϣ,androidƽ̨û�д�����Ϣ
*/
void shareCallback(int platform, int stCode, string& errorMsg)
{
	if (stCode == 100)
	{
		CCLog("#### HelloWorld ��ʼ����");
	}
	else if (stCode == 200)
	{
		CCLog("#### HelloWorld ����ɹ�");
	}
	else
	{
		CCLog("#### HelloWorld �������");
	}

	CCLog("platform num is : %d.", platform);
}
/*
*��Ȩ�ص�
* @param platform Ҫ��Ȩ��ƽ̨
* @param stCode ������, 200������Ȩ�ɹ�, 100����ʼ��Ȩ, 0������Ȩ����, -1����ȡ����Ȩ
* @param data ��Ȩʱ���ص�����
*/
void authCallback(int platform, int stCode, map<string, string>& data)
{
	if (stCode == 100)
	{
		CCLog("#### ��Ȩ��ʼ");
	}
	else if (stCode == 200)
	{
		CCLog("#### ��Ȩ���");
	}
	else if (stCode == 0)
	{
		CCLog("#### ��Ȩ����");
	}
	else if (stCode == -1)
	{
		CCLog("#### ȡ����Ȩ");
	}

	// ������Ȩ����, �����Ȩʧ��,������������Ϣ
	map<string, string>::iterator it = data.begin();
	for (; it != data.end(); ++it) {
		CCLog("#### data  %s -> %s.", it->first.c_str(), it->second.c_str());
	}
}
Scene* RankLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = RankLayer::create();

	scene->addChild(layer);

	return scene;
}
bool RankLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getVisibleSize();
	auto rootNode = CSLoader::createNode("RankScene.csb");
	addChild(rootNode);
	//��ȡ�ı���
	auto Score1 = (ui::Text*)rootNode->getChildByName("Text_2");
	Score1->setText(UserDefault::getInstance()->getStringForKey("user_score2"));
	auto Score2 = (ui::Text*)rootNode->getChildByName("Text_3");
	Score2->setText(UserDefault::getInstance()->getStringForKey("user_score3"));
	auto Score3 = (ui::Text*)rootNode->getChildByName("Text_4");
	Score3->setText(UserDefault::getInstance()->getStringForKey("user_score4"));
	auto Score4 = (ui::Text*)rootNode->getChildByName("Text_5");
	Score4->setText(UserDefault::getInstance()->getStringForKey("user_score5"));
	auto Score5 = (ui::Text*)rootNode->getChildByName("Text_6");
	Score5->setText(UserDefault::getInstance()->getStringForKey("user_score6"));

	auto button1 = (ui::Button*)rootNode->getChildByName("Button_1");
	button1->addTouchEventListener(this, toucheventselector(RankLayer::OnClickBack));
	// ����share button, ����1Ϊ��������µ�ͼƬ, ����2Ϊ�û�������ͼƬ, ����3Ϊ����app key, ������Ϊ����ص�.
	UMShareButton *shareButton = UMShareButton::create("share.png", "share2.png", "58107b3365b6d610a2000613", share_selector(shareCallback));
	vector<int>* platforms = new vector<int>();
	platforms->push_back(QZONE);
	platforms->push_back(QQ);
	platforms->push_back(WEIXIN);
	platforms->push_back(WEIXIN_CIRCLE);
	shareButton->setPlatforms(platforms);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	shareButton->setShareImage("share.png");

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	shareButton->setShareImage("share.png");

#endif

	// ���÷���ص�
	shareButton->setShareCallback(share_selector(shareCallback));
	shareButton->setPosition(ccp(640, 80));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create();
	// ����share button
	pMenu->addChild(shareButton, 1);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	// ********************** ����ƽ̨��Ϣ ***************************f9cad1d153aaa97925a2e2b5fa63d59f
	CCUMSocialSDK *sdk = shareButton->getSocialSDK();
	sdk->setQQAppIdAndAppKey("100424468", "c7394704798a158208a74ab60104f0ba");
	sdk->setWeiXinAppInfo("wx485ab7ca6a7e02d1", "f9cad1d153aaa97925a2e2b5fa63d59f");
	// �����û����һ��ͼ�ķ���ʱ�û���ת����Ŀ��ҳ��, һ��Ϊapp��ҳ��������ҳ��
	sdk->setTargetUrl("http://www.umeng.com/social");
	// ����΢�ŵķ�������
	sdk->setPlatformShareContent(WEIXIN, "WEIXIN share ����",
		"CloseNormal.png", "WEIXIN-title",
		"http://www.baidu.com");
	// ����QQ�ķ�������
	sdk->setPlatformShareContent(QQ, "QQ share ����", "CloseNormal.png",
		"QQ-title", "http://blog.csdn.net/bboyfeiyu");
	//     // �򿪻��߹ر�log
	sdk->setLogEnable(true);
	// **********************   END ***************************

	return true;
}
void RankLayer::OnClickBack(Ref* pSende, TouchEventType eventtype){
	switch (eventtype)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:SimpleAudioEngine::getInstance()->playEffect("sound/effcet_ui_fanhui.mp3"); break;
	case TouchEventType::TOUCH_EVENT_MOVED:break;
	case TouchEventType::TOUCH_EVENT_ENDED:Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainScene::createScene())); break;
	case TouchEventType::TOUCH_EVENT_CANCELED:break;
	default:
		break;
	}

}

