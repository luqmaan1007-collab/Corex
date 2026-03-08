#pragma once
#include "token.h"
#include <vector>
#include <string>
#include <iostream>
#include <functional>
namespace corex {
enum class Severity { NOTE, WARNING, ERROR, FATAL };
struct Diagnostic {
    Severity sev; std::string code,message,hint; SourceSpan span;
    Diagnostic(Severity s,std::string c,std::string m,SourceSpan sp)
        :sev(s),code(std::move(c)),message(std::move(m)),span(std::move(sp)){}
    bool isError()const{return sev==Severity::ERROR||sev==Severity::FATAL;}
    std::string render()const{
        std::string s=span.str()+": "+
            (sev==Severity::ERROR?"error":sev==Severity::WARNING?"warning":"note")+
            "["+code+"]: "+message+"\n";
        if(!hint.empty())s+="  hint: "+hint+"\n";
        return s;
    }
};
class DiagnosticEngine {
public:
    using Handler=std::function<void(const Diagnostic&)>;
    explicit DiagnosticEngine(Handler h=nullptr):handler_(std::move(h)){}
    void emitError(const std::string&c,const std::string&m,SourceSpan s,const std::string&hint=""){
        Diagnostic d(Severity::ERROR,c,m,s);d.hint=hint;emit(d);}
    void emitWarning(const std::string&c,const std::string&m,SourceSpan s,const std::string&hint=""){
        Diagnostic d(Severity::WARNING,c,m,s);d.hint=hint;emit(d);}
    void emitFatal(const std::string&c,const std::string&m,SourceSpan s){
        Diagnostic d(Severity::FATAL,c,m,s);emit(d);throw std::runtime_error("fatal: "+m);}
    bool hasErrors()const{return errs_>0;}
    int errorCount()const{return errs_;}
    int warnCount()const{return warns_;}
    const std::vector<Diagnostic>&all()const{return diags_;}
    void printAll(std::ostream&os=std::cerr)const{for(auto&d:diags_)os<<d.render();}
    void clear(){diags_.clear();errs_=0;warns_=0;}
private:
    void emit(const Diagnostic&d){
        diags_.push_back(d);
        if(d.sev==Severity::ERROR||d.sev==Severity::FATAL)++errs_;
        if(d.sev==Severity::WARNING)++warns_;
        if(handler_)handler_(d);else std::cerr<<d.render();
    }
    std::vector<Diagnostic>diags_;
    int errs_=0,warns_=0;
    Handler handler_;
};
} // namespace corex
