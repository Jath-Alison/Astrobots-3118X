using MVC_WithAngular.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MVC_WithAngular.Controllers
{
    public class KCModulesController : Controller
    {
        // GET: KCModules
        public ActionResult Index()
        {
            KSADSCOMPEntities OE = new KSADSCOMPEntities();
            IQueryable<ModuleMst> mod = OE.ModuleMsts;
            var InterviewModules = mod.Where(x => x.ScreeningGroupID == 1).ToList<ModuleMst>();
            return Json(InterviewModules, JsonRequestBehavior.AllowGet);
        }
    }
}