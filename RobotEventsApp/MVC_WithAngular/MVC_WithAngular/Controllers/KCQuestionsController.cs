using MVC_WithAngular.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MVC_WithAngular.Controllers
{
    public class KCQuestionsController : Controller
    {
        // GET: KCQuestions
        public ActionResult GetQuestions()
        {
            KSADSCOMPEntities OE = new KSADSCOMPEntities();
            IQueryable<QuestionMst> Qmst = OE.QuestionMsts;
            var QuestionData = Qmst.Where(x => x.ScreeningGroupId == 1 && x.SymptomID == 1).ToList<QuestionMst>();
            return Json(QuestionData, JsonRequestBehavior.AllowGet);
        }
        public ActionResult GetQuestionsByModID(int id)
        {
            KSADSCOMPEntities OE = new KSADSCOMPEntities();
            IQueryable<QuestionMst> Qmst = OE.QuestionMsts;
            var QuestionData = Qmst.Where(x => x.ScreeningGroupId == 1 && x.ModuleID == id).ToList<QuestionMst>();
            return Json(QuestionData, JsonRequestBehavior.AllowGet);
        }
    }
}