using MVC_WithAngular.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;

namespace MVC_WithAngular.Controllers
{
    public class RobotEventsController : Controller
    {
        // GET: RobotEvents
        public ActionResult Index()
        {
            return View();
        }
        public ActionResult GetTeams()
        {
            string Json_Res = "";
            var request = (HttpWebRequest)WebRequest.Create("https://www.robotevents.com/api/v2/teams");
            request.Accept = "application/json";
            request.Method = "GET";
            request.Headers["Authorization"] = "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJhdWQiOiIzIiwianRpIjoiNzlmZTBmYWVjNzhjZTlmMmU0M2I3NGM0NmRjMzRhMGZkZGU2MjU5ZGFhZWQ2MDc2MzAwZDFmOWU3Y2RmMGEwNjJjNjc2MTQyMzAxNjgxZTAiLCJpYXQiOjE2OTEzNTkzMTAuNTI2Njc1OSwibmJmIjoxNjkxMzU5MzEwLjUyNjY3OSwiZXhwIjoyNjM4MTM0MTEwLjUxMDc3Niwic3ViIjoiMTEzOTg1Iiwic2NvcGVzIjpbXX0.LIbNy1-LIY68vUD40JEdn6gKahcnFAKD4ytWsBDGrSDhf86tIkkDKhSLqpi1P-xtv1ofltH4qUo5wrVfskuW9Xs311PDbF4dk9BJo921CpnQfvAqEh18y8gG0dSIv8fP5eZWWcItcVncMs7QkAUzmRNrG2P8AswCSPMv57SAh1uIreeIUmmiMGaMN6tmY_gZpzHWlNdHyyrk0_5AmmGhjBY6tUhi-avYjkWCMss1iujxQx3POF2pmpK4RO2K2N-Lh4148moQCVMREIo5LcpB3K_tnS8KVgWvgrY9h5_Z_SsbfFir1_3VJMgAuX4Vwq3LBKg37T6piikRJiIjF2rBf0771i_XbJW0csKGm0TX_fgLWc1mUHCUXy4zVOpPnU55AMC5NQFFKucGwldzNxCZBhmfIQKVXsw5Fx35VHFWPhQsHM0ybiPJlkAPXSJ18DcE0saktLe4J0xhfszoQ-5dNWn1VxXjBJnRxxKFYjNzc8J1Hk82Rt4fc8PlCQH2PFBscw5IkgeOFsyvMjkc5TWfoNnEVwv71xpaMebWwkKPhuF7q36HgaJtWFaAqaSSEPYo5PdaU6GxLKM9YipZU_AS4t_N5FlSOWIQChjeNPfSIHcXcGSVYbwX0y8-lbf1dQhCm9BQqtPSgp2Hs0zYIOWCKwHLCd75Lb8FrU7nS8Qi0_0";          
            using (var response = (HttpWebResponse)request.GetResponse())
            {
                var ResponseString = new StreamReader(response.GetResponseStream()).ReadToEnd();
                Json_Res = ResponseString.ToString();
            }
            Json(Json_Res, JsonRequestBehavior.AllowGet)
            return Json_Res;
        }
    }

}