/*-------------------------------------------------------------------------
 *
 * planner.h
 *	  prototypes for planner.c.
 *
 *
 * Portions Copyright (c) 1996-2016, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/optimizer/planner.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef PLANNER_H
#define PLANNER_H

#include "nodes/plannodes.h"
#include "nodes/relation.h"
#include "optimizer/clauses.h"


/* Hook for plugins to get control in planner() */
typedef PlannedStmt *(*planner_hook_type) (Query *parse,
													   int cursorOptions,
												  ParamListInfo boundParams);
extern PGDLLIMPORT planner_hook_type planner_hook;

/* Hook for plugins to get control when grouping_planner() plans upper rels */
typedef void (*create_upper_paths_hook_type) (PlannerInfo *root,
													 UpperRelationKind stage,
													   RelOptInfo *input_rel,
													 RelOptInfo *output_rel);
extern PGDLLIMPORT create_upper_paths_hook_type create_upper_paths_hook;


extern PlannedStmt *planner(Query *parse, int cursorOptions,
		ParamListInfo boundParams);
extern PlannedStmt *standard_planner(Query *parse, int cursorOptions,
				 ParamListInfo boundParams);

extern PlannerInfo *subquery_planner(PlannerGlobal *glob, Query *parse,
				 PlannerInfo *parent_root,
				 bool hasRecursion, double tuple_fraction,
				 PlannerConfig *config);

extern bool choose_hashed_grouping(PlannerInfo *root,
								   double tuple_fraction, double limit_tuples,
								   double path_rows, int path_width,
								   Path *cheapest_path,
								   Path *sorted_path,
								   double dNumGroups,
								   AggClauseCosts *agg_costs);

extern RowMarkType select_rowmark_type(RangeTblEntry *rte,
					LockClauseStrength strength);

extern void mark_partial_aggref(Aggref *agg, AggSplit aggsplit);

extern Path *get_cheapest_fractional_path(RelOptInfo *rel,
							 double tuple_fraction);

extern Expr *expression_planner(Expr *expr);

extern Expr *preprocess_phv_expression(PlannerInfo *root, Expr *expr);

extern bool plan_cluster_use_sort(Oid tableOid, Oid indexOid);

#endif   /* PLANNER_H */
