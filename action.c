#include "web_api.h"

Action()
{

	
	// postId를 추출하기 위함 파라미터 값
    web_reg_save_param("postId", "LB=postId\":\"", "RB=\",\"uid", LAST);



	lr_start_transaction("01_feed list");


	// 여기서부터 첫 번째 feed 가져옴
	web_add_header("ver", "1.1.1");
/*
	web_custom_request("web_custom_request",
        "URL=http://api.snapstyle.to/api/v1/post/list",
        "Method=GET",
        "TargetFrame=",
        "Resource=0",
        "Referer=",
        "Mode=HTTP",
        LAST);
*/

	web_custom_request("web_custom_request",
        "URL=https://api.snapstyle.to/api/v1/post/list",
        "Method=GET",
        "TargetFrame=",
        "Resource=0",
        "Referer=",
        "Mode=HTTP",
        LAST);

	

	lr_end_transaction("01_feed list", LR_AUTO);


	// postId 제대로 가져오는지 결과창에 출력
	lr_output_message("%s", lr_eval_string("{postId}"));



 	/***
     ##에러 체크
          특정 문자열의 시작과 끝을 지정하고,
          밑에서 그 안에 들어가 있는 문자를 확인한다. */
    // web_reg_save_param("ErrorCheck", "LB=profile", "RB=Url", LAST);
    web_reg_save_param("ErrorCheck", "LB=clo", "RB=front", LAST);
     /**** 에러 체크 문자열 지정 끝 ****/


     lr_start_transaction("02_feed 후 값 전달");

	// 여기서부터 postId 치환 부분
	web_add_header("ver", "1.1.1");

	web_custom_request("web_custom_request2",
        "URL=https://api.snapstyle.to/api/v1/post/get?postId={postId}",
      //  "URL=https://api.snapstyle.to/api/v1/post/get?postId=8f88d923-a9bd-44f2-9102-504f2c4d3492",
        "Method=GET",
        "TargetFrame=",
        "Resource=0",
        "Referer=",
        "Mode=HTTP",
        LAST);

     /****
     ##에러 문자열 확인. 중간 문자가 있는지 확인한다.
     ***/
//      if (strcmp(lr_eval_string("{ErrorCheck}"), "Thumb")==0)
      if (strcmp(lr_eval_string("{ErrorCheck}"), "ud")==0)
         lr_end_transaction("02_feed 후 값 전달", LR_PASS);
      else {
         lr_end_transaction("02_feed 후 값 전달", LR_FAIL);
      }

	
	return 0;
}
