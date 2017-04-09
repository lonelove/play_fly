#include "RnakLayer.h"
#include"MainScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
// 引入相关的头文件
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
// 使用友盟命令空间
USING_NS_UM_SOCIAL;
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
/*
* 分享回调
* @param platform 要分享到的目标平台
* @param stCode 返回码, 200代表分享成功, 100代表开始分享
* @param errorMsg 分享失败时的错误信息,android平台没有错误信息
*/
void shareCallback(int platform, int stCode, string& errorMsg)
{
	if (stCode == 100)
	{
		CCLog("#### HelloWorld 开始分享");
	}
	else if (stCode == 200)
	{
		CCLog("#### HelloWorld 分享成功");
	}
	else
	{
		CCLog("#### HelloWorld 分享出错");
	}

	CCLog("platform num is : %d.", platform);
}
/*
*授权回调
* @param platform 要授权的平台
* @param stCode 返回码, 200代表授权成功, 100代表开始授权, 0代表授权出错, -1代表取消授权
* @param data 授权时返回的数据
*/
void authCallback(int platform, int stCode, map<string, string>& data)
{
	if (stCode == 100)
	{
		CCLog("#### 授权开始");
	}
	else if (stCode == 200)
	{
		CCLog("#### 授权完成");
	}
	else if (stCode == 0)
	{
		CCLog("#### 授权出错");
	}
	else if (stCode == -1)
	{
		CCLog("#### 取消授权");
	}

	// 输入授权数据, 如果授权失败,则会输出错误信息
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
	//获取文本框
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
	// 友盟share button, 参数1为正常情况下的图片, 参数2为用户点击后的图片, 参数3为友盟app key, 参数四为分享回调.
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

	// 设置分享回调
	shareButton->setShareCallback(share_selector(shareCallback));
	shareButton->setPosition(ccp(640, 80));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create();
	// 友盟share button
	pMenu->addChild(shareButton, 1);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	// ********************** 设置平台信息 ***************************f9cad1d153aaa97925a2e2b5fa63d59f
	CCUMSocialSDK *sdk = shareButton->getSocialSDK();
	sdk->setQQAppIdAndAppKey("100424468", "c7394704798a158208a74ab60104f0ba");
	sdk->setWeiXinAppInfo("wx485ab7ca6a7e02d1", "f9cad1d153aaa97925a2e2b5fa63d59f");
	// 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
	sdk->setTargetUrl("http://www.umeng.com/social");
	// 设置微信的分享内容
	sdk->setPlatformShareContent(WEIXIN, "WEIXIN share 内容",
		"CloseNormal.png", "WEIXIN-title",
		"http://www.baidu.com");
	// 设置QQ的分享内容
	sdk->setPlatformShareContent(QQ, "QQ share 内容", "CloseNormal.png",
		"QQ-title", "http://blog.csdn.net/bboyfeiyu");
	//     // 打开或者关闭log
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

