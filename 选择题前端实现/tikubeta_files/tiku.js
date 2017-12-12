var timeState = true;//时间状态 默认为true 开启时间
var HH = 0;//时
var mm = 0;//分
var ss = 0;//秒
/*实现计时器*/
var time = setInterval(function () {
    if (timeState) {
        if (HH == 24) HH = 0;
        str = "";
        if (++ss == 60) {
            if (++mm == 60) { HH++; mm = 0; }
            ss = 0;
        }
        str += HH < 10 ? "0" + HH : HH;
        str += ":";
        str += mm < 10 ? "0" + mm : mm;
        str += ":";
        str += ss < 10 ? "0" + ss : ss;
        $(".time").text(str);
    } else {
        $(".time").text(str);
    }
}, 1000);
/*开启或者停止时间*/
    $(".time-stop").click(function () {
        timeState = false;
        $(this).hide();
        $(".time-start").show();
    });
    $(".time-start").click(function () {
        timeState = true;
        $(this).hide();
        $(".time-stop").show();
    });

	
	
var i=0;

			var r1 =
            {
                qid: 0,
                question: "这是第1题",
                options: { "A": "hello", "B": "yo", "C": "greetings" },
                type: ""
            };
var r=r1;			
			var r2 =
            {
                qid: 1,
                question: "这是第2题",
                options: { "A": "你好", "B": "qaq", "C": "123" },
                type: ""
            };
			
			var r3 =
            {
                qid: 2,
                question: "这是第3题",
                options: { "A": "red", "B": "yellow", "C": "green" },
                type: ""
            };
			
			
			var r4 =
            {
                qid: 3,
                question: "这是第4题",
                options: { "A": "2", "B": "4", "C": "6" },
                type: ""
            };
			
			var r5 =
            {
                qid: 4,
                question: "这是第5题",
                options: { "A": "f", "B": "u", "C": "c*" },
                type: ""
            };

	function getQuestion() {
		var getQuestionUrl = "";
		var result;
		$.ajax(
			{
				url: getQuestionUrl,
				type: "get",
				data: {},
				success: function (re) {
					result = re;
				}
			}
		);
		return result;
	}

	function alterQuestion(quest) {
		$("#question p").text(quest.question).attr("qid", quest.qid);
		$("#options").empty();
		var a = "<li><input type = \"radio\" name = \"option\" value = \"";
		var b = "\">"
		var c = "</li>"
		for (op in quest.options) {
			$("#options").append(a + op + b + quest.options[op] + c);
		}
	}
	
	function alterQuestionbynum(num){
		i=parseInt(num);
		r=eval("r"+i);
		alterQuestion(r);
	}
	
	function alterprevQuestion() {
		i=i-1;
		r=eval("r"+i);
		alterQuestion(r);
	}
	
	function alternextQuestion() {
		i=i+1;
		r=eval("r"+i);
		alterQuestion(r);
	}

	function checkAnswer() {
		var checkAnswerUrl = "";
		var ans = $("#options :radio:checked");
		if(ans.length==0)
		{
			console.log("must select one");
			return;
		}
		ans = ans[0].value;
		var response;
		response = new Object();
		response.right = 0;
		// console.log(ans);
		// $.ajax(
		//     {
		//         url: checkAnswerUrl,
		//         type: "get",
		//         data: { "qid": 0, "answer": ans },
		//         success: function (re) {
		//             response = re;
		//         }
		//     }
		// );
		if (response.right == 1)
			$("#result").text("正确");
		else
			$("#result").text("错误");

	}
	function getAnswer() {
		var getAnswerUrl = "";
		var qid = $("#question p").attr("qid");
		var response;
		$.ajax(
			{
				url: getAnswerUrl,
				type: "get",
				data: { "qid": qid },
				success: function (re) { response = re; }
			}
		);
		return response;
	}